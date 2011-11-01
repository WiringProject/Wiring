/* $Id: Supervisor.cpp 1198 2011-06-14 21:08:27Z bhagman $
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

#include "Supervisor.h"

//provide a global object (without using singleton pattern)
RuleSupervisor Supervisor;

