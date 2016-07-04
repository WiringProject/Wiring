#ifndef __HASHMAP_H__
#define __HASHMAP_H__


#include <Arduino.h>


/* Handle association */
template<typename hash,typename map>

class HashType {

	public:

		HashType(){
			reset();
		}
		
		~HashType(){ //distruttore
		
			//Serial.println("HashType destructing...");
			//hashCode.~hash();
			//hashCode.~hash();
			//Serial.println("HashType destruct");
		}
	
		HashType(hash code, map value): hashCode(code), mappedValue(value){}
	
		void reset(){
			hashCode = 0; mappedValue = 0;
		}
	
		hash getHash(){
			return hashCode;
		}
	
		void setHash(hash code){
			hashCode = code;
		}
	
		map getValue(){
			return mappedValue;
		}
	
		void setValue(map value){
			mappedValue = value;
		}
	
		HashType& operator()(hash code, map value){
			setHash( code );
			setValue( value );
		}
	private:
		hash hashCode;
		map mappedValue;
};


//classe nodo per la lista

template<typename hash, typename map>

class HashNode {

	public:

		HashNode(hash code, map value) {
		
			hashType = new HashType<hash, map>(code, value);
		
			previus = 0;
			
			next = 0;
		
		}
		
		~HashNode() { //distruttore
			//Serial.println("HashNode destructing...");
			
			delete hashType;
			
			//Serial.println("HashNode destruct");
		}
		
		HashType<hash, map> * getHashType() {
			return hashType;
		}
		
		HashNode<hash, map> * getPrevius() {
			return previus;
		}
		
		HashNode<hash, map> * getNext() {
			return next;
		}
		
		void setPrevius(HashNode<hash, map> * previus) {
		
			this->previus = previus;
		
		}
		
		void setNext(HashNode<hash, map> * next) {
		
			this->next = next;
		
		}
		

	private:

		HashType<hash, map> * hashType;
		
		HashNode * previus;
		
		HashNode * next;


};


//classe che gestisce l'hash map
template<typename hash,typename map>
class HashMap {

	private:
		HashNode<hash, map> * start;
		
		HashNode<hash, map> * finish;
		
		HashNode<hash, map> * position;
		
		int size;
		
		
		HashNode<hash, map> * getPosition(hash key) { //get di un elemento
			
			for(HashNode<hash, map> * pointer = start; pointer != 0; pointer = pointer->getNext()) {
			
				HashType<hash, map> * hashType = pointer->getHashType();
		
				if (key == hashType->getHash()) {
				
					return pointer;
				
				}
				
			}
			
			return 0;
		
		}
		
		
		void remove(HashNode<hash, map> * pointer) { //rimuove l'elemento selezionato
		
			if (size == 1) { //1 elemento presente 1 elemento da eliminare
				
				//Serial.println("1 solo: remove p");
				
				start = finish = 0;
				
			} else { //più di un elemento presente
			
				if (pointer == start) { //elemto da rimuovere è la testa
					
					start = start->getNext();
				
					start->setPrevius(0);
				
				} else if (pointer == finish) { //elemnto da rimuovere è la coda
					
					finish = finish->getPrevius();
					
					finish->setNext(0);
				
				} else { //elemento da rimuovere in mezzo alla lista
					
					pointer->getPrevius()->setNext(pointer->getNext());
					
					pointer->getNext()->setPrevius(pointer->getPrevius());
					
				}
				
			}
			
			size--;
			
			
			//Serial.println("dealloc");
			
			
			delete pointer;
			
		}
		
		
	public:
	
		HashMap(){	
			
			start = 0;
			finish = 0;
			position = 0;	

			size = 0;
			
		}
		
		~HashMap(){	//distruttore
		
			//Serial.println("HashMap destructing...");
			//Serial.print("n: ");
			//Serial.println(length());
			
			if (moveToFirst()) {
				
				do {
					
					remove();
					
				} while (moveToNext());
			
			}
			
			
			//Serial.println("HashMap destruct");
			
		}
		
		void put(hash key, map value) { //inserisce un nuovo nodo contenente i dati
			
			if (start == 0) {
				
				start = finish = new HashNode<hash, map>(key, value);
				
			} else {
				
				HashNode<hash, map> * temp = new HashNode<hash, map>(key, value);
				
				finish->setNext(temp);
				
				temp->setPrevius(finish);
				
				finish = temp;
				
			}
			
			size++;
			
		}
		
		map getValue(hash key) { //get di un elemento
		
			HashNode<hash, map> * pointer = getPosition(key);
			
			if (pointer != 0) {
				
				return pointer->getHashType()->getValue();
				
			}
		
		}
		
		
		int containsKey(hash key) { //1 se contiene la chiave 0 altrimenti
			
			if (getPosition(key) != 0) {
				
				return 1;
				
			} else {
			
				return 0;
			
			}
			
		}
		
		void remove(hash key) {
			
			HashNode<hash, map> * pointer = getPosition(key);
			
			if (pointer != 0) {
				
				remove(pointer);
				
			}
			
		
		}
		
		int length() {
			
			return size;
			
		}
		
		
		//metodi per implementare la mia interfaccia iterable 1 ok, 0 non esistono più elementi
		int moveToFirst() {
			
			if (start != 0) {
				
				position = start;
				
				return 1;
				
			} else {
				
				return 0;
				
			}
			
		}
		
		int moveToLast() {
		
			if (finish != 0) {
				
				position = finish;
				
				return 1;
				
			} else {
				
				return 0;
				
			}
			
		}
		
		
		int moveToNext() {
			
			if (position->getNext() != 0) {
				
				position = position->getNext();
				
				return 1;
				
			} else {
				
				return 0;
				
			}
		
		}
		
		int moveToPrev() {
			
			if (position->getPrevius() != 0) {
				
				position = position->getPrevius();
				
				return 1;
				
			} else {
				
				return 0;
				
			}
		
		}
		
		
		map getValue() { //get di un elemento
			
			if (position != 0) {
				
				return position->getHashType()->getValue();
				
			}
		
		}
		
		hash getKey() { //get hash di un elemento
		
			if (position != 0) {
				
				return position->getHashType()->getHash();
				
			}
		
		}
		
		void remove() {
		
			if (position != 0) {
			
				if (size == 1) { //1 ele 1 da rimuovere					
					
					//Serial.println("1 solo: remove");
					
					remove(position);
					
					position = 0;
			
				} else {
				
					if (position == start) {
					
						remove(position);
					
						position = start;
				
					} else {
					
						remove(position);
					
						position = position->getPrevius();
					
					}
				
				}
			
			}
			
		}
		
		
};

#endif
