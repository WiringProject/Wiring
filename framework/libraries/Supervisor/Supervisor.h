/* $Id: Supervisor.h 1198 2011-06-14 21:08:27Z bhagman $
||
|| @author         Alexander Brevig <abrevig@wiring.org.co>
|| @url            http://wiring.org.co/
|| @url            http://alexanderbrevig.com/
|| @contribution   Brett Hagman <bhagman@wiring.org.co>
||
|| @description
|| | Supervise a set of rules that automatically fire a handler
|| | for when the rule is broken.
|| | Rules operate on a single variable, and need a supporting
|| | check function and the beforementioned handler.
|| |
|| | Wiring Cross-platform Library
|| #
||
|| @license Please see cores/Common/License.txt.
||
*/

#ifndef SUPERVISOR_H
#define SUPERVISOR_H

/*
  Provide a templateless definition of a rule
  so that the RuleSupervisor can stay Cross-platform
*/
class BaseRule
{
  public:
    void check()
    {
      onCheck();
    }
    BaseRule *next;

  protected:
    virtual void onCheck() {};
};

/*
  Type specification of a rule
*/
template<typename T>
class SupervisedRule : public BaseRule
{
  public:
    SupervisedRule()
    {
      next = 0;
      cb_check = 0;
    }
    SupervisedRule(T &val, unsigned char(*check)(T), void (*handle)(T&))
    {
      value = &val;
      cb_check = check;
      cb_handle = handle;
    }
    ///call the neccessary callbacks for this rule
    void onCheck()
    {
      if (cb_check)
      {
        //check if the rule is still true
        if (!cb_check(*value))
        {
          //if not, then handle it
          if (cb_handle)
          {
            cb_handle(*value);
          }
        }
      }
    }
    T *value;
    unsigned char(*cb_check)(T);
    void (*cb_handle)(T&);
};

class RuleSupervisor
{
  public:
    /*
    || @description
    || | Add a rule for this Supervisor to supervise
    || #
    ||
    || @parameter r the SupervisedRule to add
    */
    void addRule(BaseRule &r)
    {
      BaseRule *rule = &rootRule;
      while (rule->next)
      {
        rule = rule->next;
      }
      rule->next = &r;
    }
    /*
    || @description
    || | Add a rule for this Supervisor to supervise
    || #
    ||
    || @parameter r the SupervisedRule to add
    */
    void removeRule(BaseRule &r)
    {
      BaseRule *rule = &rootRule;
      while (rule->next)
      {
        if (rule->next == &r)
        {
          rule->next = rule->next->next;
          break;
        }
        rule = rule->next;
      }
    }
    /*
    || @description
    || | Check all rules for this Supervisor
    || #
    */
    void checkRules()
    {
      BaseRule *rule = &rootRule;
      do
      {
        rule->check();
        rule = rule->next;
      }
      while (rule);
    }
  private:
    BaseRule rootRule;
};

extern RuleSupervisor Supervisor;

#endif
// SUPERVISOR_H
