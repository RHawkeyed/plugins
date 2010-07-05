#!/bin/bash

UT_TESTCASES=""

for TEST in `ls -d ut_*`; do
	if [ -x $TEST/$TEST ]; then

TESTCASE_TEMPLATE="<case name=\"$TEST\" description=\"$TEST\" requirement=\"\" timeout=\"120\">
        <step expected_result=\"0\">/usr/lib/meego-keyboard-tests/$TEST/$TEST</step>
      </case>
      "

	    UT_TESTCASES="${UT_TESTCASES}${TESTCASE_TEMPLATE}"
	fi
done

TESTSUITE_TEMPLATE="<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>
<testdefinition version=\"0.1\">
  <suite name=\"meego-keyboard-tests\"> 
    <set name=\"unit_tests\" description=\"Unit Tests\">

      $UT_TESTCASES

      <environments>
        <scratchbox>false</scratchbox>
        <hardware>true</hardware>    
      </environments> 

    </set>
  </suite>
</testdefinition>"

echo "$TESTSUITE_TEMPLATE"
