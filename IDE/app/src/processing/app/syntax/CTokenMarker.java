/*
 * CTokenMarker.java - C token marker
 * Copyright (C) 1998, 1999 Slava Pestov
 *
 * You may use and modify this package for any purpose. Redistribution is
 * permitted, in both source and binary form, provided that this notice
 * remains intact in all source distributions of this package.
 */

package processing.app.syntax;

import javax.swing.text.Segment;

/**
 * C token marker.
 *
 * @author Slava Pestov
 * @version $Id: CTokenMarker.java 1083 2011-05-05 06:11:20Z h $
 */
public class CTokenMarker extends TokenMarker {
  public CTokenMarker() {
    this(true, getKeywords());
  }

  public CTokenMarker(boolean cpp, KeywordMap keywords) {
    this.cpp = cpp;
    this.keywords = keywords;
  }

  public byte markTokensImpl(byte token, Segment line, int lineIndex) {
    char[] array = line.array;
    int offset = line.offset;
    lastOffset = offset;
    lastKeyword = offset;
    int mlength = line.count + offset;
    boolean backslash = false;

    loop: for (int i = offset; i < mlength; i++) {
      int i1 = (i + 1);

      char c = array[i];
      if (c == '\\') {
        backslash = !backslash;
        continue;
      }

      switch (token) {
      case Token.NULL:
        switch (c) {
        case '#':
          if (backslash)
            backslash = false;
          else if (cpp) {
            if (doKeyword(line, i, c))
              break;
            addToken(i - lastOffset, token);
            addToken(mlength - i, Token.KEYWORD2);
            lastOffset = lastKeyword = mlength;
            break loop;
          }
          break;
        case '"':
          doKeyword(line, i, c);
          if (backslash)
            backslash = false;
          else {
            addToken(i - lastOffset, token);
            token = Token.LITERAL1;
            lastOffset = lastKeyword = i;
          }
          break;
        case '\'':
          doKeyword(line, i, c);
          if (backslash)
            backslash = false;
          else {
            addToken(i - lastOffset, token);
            token = Token.LITERAL2;
            lastOffset = lastKeyword = i;
          }
          break;
        case ':':
          if (lastKeyword == offset) {
            if (doKeyword(line, i, c))
              break;
            backslash = false;
            addToken(i1 - lastOffset, Token.LABEL);
            lastOffset = lastKeyword = i1;
          } else if (doKeyword(line, i, c))
            break;
          break;
        case '/':
          backslash = false;
          doKeyword(line, i, c);
          if (mlength - i > 1) {
            switch (array[i1]) {
            case '*':
              addToken(i - lastOffset, token);
              lastOffset = lastKeyword = i;
              if (mlength - i > 2 && array[i + 2] == '*')
                token = Token.COMMENT2;
              else
                token = Token.COMMENT1;
              break;
            case '/':
              addToken(i - lastOffset, token);
              addToken(mlength - i, Token.COMMENT1);
              lastOffset = lastKeyword = mlength;
              break loop;
            }
            i++; // jdf- fix http://dev.processing.org/bugs/show_bug.cgi?id=609
          }
          break;
        default:
          backslash = false;
          if (!Character.isLetterOrDigit(c) && c != '_')
            doKeyword(line, i, c);
          break;
        }
        break;
      case Token.COMMENT1:
      case Token.COMMENT2:
        backslash = false;
        if (c == '*' && mlength - i > 1) {
          if (array[i1] == '/') {
            i++;
            addToken((i + 1) - lastOffset, token);
            token = Token.NULL;
            lastOffset = lastKeyword = i + 1;
          }
        }
        break;
      case Token.LITERAL1:
        if (backslash)
          backslash = false;
        else if (c == '"') {
          addToken(i1 - lastOffset, token);
          token = Token.NULL;
          lastOffset = lastKeyword = i1;
        }
        break;
      case Token.LITERAL2:
        if (backslash)
          backslash = false;
        else if (c == '\'') {
          addToken(i1 - lastOffset, Token.LITERAL1);
          token = Token.NULL;
          lastOffset = lastKeyword = i1;
        }
        break;
      default:
        throw new InternalError("Invalid state: " + token);
      }
    }

    if (token == Token.NULL)
      doKeyword(line, mlength, '\0');

    switch (token) {
    case Token.LITERAL1:
    case Token.LITERAL2:
      addToken(mlength - lastOffset, Token.INVALID);
      token = Token.NULL;
      break;
    case Token.KEYWORD2:
      addToken(mlength - lastOffset, token);
      if (!backslash)
        token = Token.NULL;
      addToken(mlength - lastOffset, token);
      break;
    default:
      addToken(mlength - lastOffset, token);
      break;
    }

    return token;
  }

  public static KeywordMap getKeywords() {
    return cKeywords;
  }

  // private members
  private static KeywordMap cKeywords = new KeywordMap(false) {
    {
      add("char",Token.KEYWORD3);
      add("double",Token.KEYWORD3);
      add("enum",Token.KEYWORD3);
      add("float",Token.KEYWORD3);
      add("int",Token.KEYWORD3);
      add("long",Token.KEYWORD3);
      add("short",Token.KEYWORD3);
      add("signed",Token.KEYWORD3);
      add("struct",Token.KEYWORD3);
      add("typedef",Token.KEYWORD3);
      add("union",Token.KEYWORD3);
      add("unsigned",Token.KEYWORD3);
      add("void",Token.KEYWORD3);
      add("auto",Token.KEYWORD1);
      add("const",Token.KEYWORD1);
      add("extern",Token.KEYWORD1);
      add("register",Token.KEYWORD1);
      add("static",Token.KEYWORD1);
      add("volatile",Token.KEYWORD1);
      add("break",Token.KEYWORD1);
      add("case",Token.KEYWORD1);
      add("continue",Token.KEYWORD1);
      add("default",Token.KEYWORD1);
      add("do",Token.KEYWORD1);
      add("else",Token.KEYWORD1);
      add("for",Token.KEYWORD1);
      add("goto",Token.KEYWORD1);
      add("if",Token.KEYWORD1);
      add("return",Token.KEYWORD1);
      add("sizeof",Token.KEYWORD1);
      add("switch",Token.KEYWORD1);
      add("while",Token.KEYWORD1);
      add("asm",Token.KEYWORD2);
      add("asmlinkage",Token.KEYWORD2);
      add("far",Token.KEYWORD2);
      add("huge",Token.KEYWORD2);
      add("inline",Token.KEYWORD2);
      add("near",Token.KEYWORD2);
      add("pascal",Token.KEYWORD2);
      add("true",Token.LITERAL2);
      add("false",Token.LITERAL2);
      add("NULL",Token.LITERAL2);
// BARRAGAN, add other keywords  
      add("and", Token.KEYWORD3);
      add("and_eq", Token.KEYWORD3);
      add("bitand", Token.KEYWORD3);
      add("bitor", Token.KEYWORD3);
      add("bool",Token.KEYWORD3);
      add("catch", Token.KEYWORD1);
      add("class", Token.KEYWORD3);
      add("compl", Token.KEYWORD3);
      add("const_cast", Token.KEYWORD3);
      add("delete", Token.KEYWORD1);
      add("dynamic_cast", Token.KEYWORD3);
      add("explicit", Token.KEYWORD1);			
      add("export", Token.KEYWORD2);
      add("friend", Token.KEYWORD1);			
      add("mutable", Token.KEYWORD3);
      add("namespace", Token.KEYWORD2);
      add("new", Token.KEYWORD1);
      add("not", Token.KEYWORD3);
      add("not_eq", Token.KEYWORD3);
      add("operator", Token.KEYWORD3);
      add("or", Token.KEYWORD3);
      add("or_eq", Token.KEYWORD3);
      add("private", Token.KEYWORD1);
      add("protected", Token.KEYWORD1);
      add("public", Token.KEYWORD1);
      add("reinterpret_cast", Token.KEYWORD3);
      add("static_cast", Token.KEYWORD3);
      add("template", Token.KEYWORD3);
      add("this", Token.LITERAL2);
      add("throw", Token.KEYWORD1);
      add("try", Token.KEYWORD1);
      add("typeid", Token.KEYWORD3);
      add("typename", Token.KEYWORD3);
      add("using", Token.KEYWORD2);
      add("virtual", Token.KEYWORD1);
      add("void", Token.KEYWORD1);		   
      add("wchar_t", Token.KEYWORD3);
      add("xor", Token.KEYWORD3);
      add("xor_eq", Token.KEYWORD3);              
    }
  };

  private boolean cpp;
  private KeywordMap keywords;
  private int lastOffset;
  private int lastKeyword;

  private boolean doKeyword(Segment line, int i, char c) {
    int i1 = i + 1;

    int len = i - lastKeyword;
    byte id = keywords.lookup(line, lastKeyword, len);
    if (id != Token.NULL) {
      if (lastKeyword != lastOffset)
        addToken(lastKeyword - lastOffset, Token.NULL);
      addToken(len, id);
      lastOffset = i;
    }
    lastKeyword = i1;
    return false;
  }
}
