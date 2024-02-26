
#include "unity.h"

#include "led.h"
#include "stm32f4xx_gpio.h"

extern GPIO_enuErrorStatus error; 
extern uint8_t LED_Status;
void test_Led_init()
{
    TEST_ASSERT_EQUAL(LED_SUCCESS , LED_enuInit());
}

void test_Led_init_2()
{
    error = NOT_VALID_AT_TYPE;
    TEST_ASSERT_EQUAL(LED_INITIALIZATION_FAILED , LED_enuInit());
}

void test_led_connected_REVERSE_ON()
{
    LED_enuSetStatus(ALARM_LED,LED_STATE_ON);
    TEST_ASSERT_EQUAL(1,LED_Status);
}

void test_led_connected_REVERSE_OFF()
{
    LED_enuSetStatus(ALARM_LED,LED_STATE_OFF);
    TEST_ASSERT_EQUAL(0,LED_Status);
}

void test_led_connected_FORWARD_ON()
{
    LED_enuSetStatus(EME_LED,LED_STATE_ON);
    TEST_ASSERT_EQUAL(0,LED_Status);
}

void test_led_connected_FORWARD_OFF()
{
    LED_enuSetStatus(EME_LED,LED_STATE_OFF);
    TEST_ASSERT_EQUAL(1,LED_Status);
}

void test_enuSetStatusParams_one()
{
    TEST_ASSERT_EQUAL(LED_SUCCESS,LED_enuSetStatus(ALARM_LED,LED_STATE_ON));
}

void test_enuSetStatusParams_two()
{
    TEST_ASSERT_EQUAL(LED_SUCCESS,LED_enuSetStatus(ALARM_LED,LED_STATE_OFF));
}

void test_enuSetStatusParams_three()
{
    TEST_ASSERT_EQUAL(LED_FAILED,LED_enuSetStatus(ALARM_LED,2));
}


void test_enuSetStatusParams_four()
{
    TEST_ASSERT_EQUAL(LED_FAILED,LED_enuSetStatus(2,LED_STATE_ON));
}

void test_enuSetStatusParams_five()
{
    TEST_ASSERT_EQUAL(LED_FAILED,LED_enuSetStatus(2,LED_STATE_OFF));
}

void test_enuSetStatusParams_six()
{
    TEST_ASSERT_EQUAL(LED_FAILED,LED_enuSetStatus(2,6));
}
void setUp(void)
{
}

void tearDown(void)
{
}



