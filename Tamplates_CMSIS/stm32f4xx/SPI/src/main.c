#include "main.h"

int main()
{
    uint8_t rcv_buff[100] = {0};
    fifo fifo_rcv = {0};
    fifo_init(&fifo_rcv, rcv_buff, sizeof(rcv_buff));
    
    uint8_t tr_buff[100] = {0};
    fifo fifo_tr = {0};
    fifo_init(&fifo_tr, tr_buff, sizeof(tr_buff));

    uint8_t state = 0;
    uint8_t password[] = "ABCD";

    RCC_init();
    SPI_1_init();

    while (1)
    {
        switch (state)
        {
            case 0:
                for (int i = 0; i < 4; ++i)
                {
                    while (!(SPI1->SR & SPI_SR_RXNE));
                    fifo_write(&fifo_rcv, SPI1->DR);
                }                
                state = 1;
                break;
            
            case 1:
                    for (int i = 0; fifo_rcv.cnt != 0; ++i)
                    {
                        if (fifo_read(&fifo_rcv) == password[i])
                        {
                            fifo_write(&fifo_tr, password[(sizeof(password) - 2) - i]);
                        }
                        else 
                        {
                            fifo_init(&fifo_tr, tr_buff, sizeof(tr_buff));
                            break;
                        }
                    }
                    state = 2;
                break;
                    
            case 2:
                    while (fifo_tr.cnt != 0)
                    {
                        SPI_send_byte(SPI1, fifo_read(&fifo_tr));
                        while (!(SPI1->SR & SPI_SR_RXNE));
                        SPI1->DR;
                    }

                    state = 0;
                break;
            
            default:
                break;
        }
    }
}
