
#include "unity.h"

#include "switch.h"
#include "stm32f4xx_gpio.h"


extern GPIO_enuErrorStatus error;
extern uint8_t pin_value;

void test_init_function_test(void)
{  
    TEST_ASSERT_EQUAL(SWITCH_SUCCESS,SWITCH_enuInit());
}


void test_init_function_test_Two(void)
{  
    error = NOT_VALID_MODE;
    TEST_ASSERT_EQUAL(SWITCH_CONFIGURATION_FAILED,SWITCH_enuInit());
}

void test_Button_Connected_PullDown_PRESSED(void)
{
    pin_value = 1;
    uint32_t switchState;
    SWITCH_enuGetStatus(ALARM_SWITCH,&switchState);
    TEST_ASSERT_EQUAL(SWITCH_STATUS_PRESSED , switchState);
}

void test_Button_Connected_PullDown_NOT_PRESSED(void)
{
    pin_value = 0;
    uint32_t switchState;
    SWITCH_enuGetStatus(ALARM_SWITCH,&switchState);
    TEST_ASSERT_EQUAL(SWITCH_STATUS_NOT_PRESSED , switchState);
}


void test_Button_Connected_PullUp_PRESSED(void)
{
    pin_value = 0;
    uint32_t switchState;
    SWITCH_enuGetStatus(A_SWITCH,&switchState);
    TEST_ASSERT_EQUAL(SWITCH_STATUS_PRESSED , switchState);
}

void test_Button_Connected_PullUp_NOT_PRESSED(void)
{
    pin_value = 1;
    uint32_t switchState;
    SWITCH_enuGetStatus(A_SWITCH,&switchState);
    TEST_ASSERT_EQUAL(SWITCH_STATUS_NOT_PRESSED , switchState);
}

void test_Wrong_Params_GetStatus_Fun()
{
    
    TEST_ASSERT_EQUAL(SWITCH_FAILED , SWITCH_enuGetStatus(ALARM_SWITCH , NULL));

}
void test_Wrong_Params_GetStatus_Fun_two()
{
    uint32_t switch_result;
    TEST_ASSERT_EQUAL(SWITCH_FAILED , SWITCH_enuGetStatus(5 , &switch_result));
}

void test_Wrong_Params_GetStatus_Fun_Three()
{
    TEST_ASSERT_EQUAL(SWITCH_FAILED , SWITCH_enuGetStatus(5 , NULL));
}

void setUp(void)
{
}

void tearDown(void)
{
}
