# Overview
upcoming

# Specific Interrupt Handlers
The XMC1400 boot kit uses different naming for interrupt handlers, i.e., instead of
```
USIC0_0_IRQHandler
USIC0_1_IRQHandler
```
it uses 
```
IRQ0_Handler
IRQ1_Handler
```
for all interrupts from `USIC`, `CCU`, etc. For details refer to `startup_XMC1400.S` file.
