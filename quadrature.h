#pragma once

#include "hardware/pio.h"

#define UI_RE_A 14
#define UI_RE_B 15


class Quadrature {
    public:
        Quadrature();
        void Setup();
        void Update();

        inline void Inc() { enc_pos ++; };
        inline void Dec() { enc_pos --; };
        inline uint8_t Pos() { return enc_pos; };

        uint8_t enc_pos = 0;
        uint8_t enc_prev = 0;
        uint8_t enc_curr = 0;
        uint8_t enc_old=0;
        uint8_t delta=0;
        uint8_t enc_new=0;

    private:
        // Use PIO 0
        PIO pio = pio0;
        // Use State Machine 0;
        const uint pio_sm = 0;

        inline void request_count(PIO pio, uint sm) { pio->txf[sm] = 1; }
        inline int32_t fetch_count(PIO pio, uint sm)
        {
            while (pio_sm_is_rx_fifo_empty(pio, sm))
                tight_loop_contents();
            return pio->rxf[sm];
        }
        inline int32_t get_count(PIO pio, uint sm)
        {
            request_count(pio, sm);
            return fetch_count(pio, sm);
        }
};