#pragma once

void UART2_Init(void);
void UART2_SendChar(char c);
void UART2_SendString(const char *str);
void UART2_SendFloat(float num, int decimals);
