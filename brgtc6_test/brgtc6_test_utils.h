#ifndef BRGTC6_TEST_UTILS_H
#define BRGTC6_TEST_UTILS_H

#include "../common.h"

// Widths
#define BRGTC6_ADDR_WIDTH 5
#define BRGTC6_CNFG_WIDTH 12
#define BRGTC6_CHNL_WIDTH 8

// Msg types
#define CHNL_MSG 0
#define CNFG_MSG 1

// Chip SPI mappings
#define CHIP_0 0
#define CHIP_1 1

// Chip reset pins
#define BRGTC6_RESET_PIN_0 6
#define BRGTC6_RESET_PIN_1 7

// Register mappings

//-------------------------------+---------------------------+-----------+-
// Loopback                      |  Addr                     |   Type    |
//-------------------------------+---------------------------+-----------+-
#define CFG_ADDR_LOOPBACK         0                          //  Write 

//-------------------------------+---------------------------+-----------+-
// Pattern Gen & Chk             |  Addr                     |   Type    |
//-------------------------------+---------------------------+-----------+-
#define CFG_ADDR_PAT_BYPASS       1                          //  Write 
#define CFG_ADDR_PATTERN_MODE     2                          //  Write 
#define CFG_ADDR_PATTERN_1_UP     3                          //  Write 
#define CFG_ADDR_PATTERN_2_UP     4                          //  Write
#define CFG_ADDR_PATTERN_1_DOWN   5                          //  Read
#define CFG_ADDR_PATTERN_2_DOWN   6                          //  Read

#define CFG_ADDR_PATTERN_STATE    7                          //  Read 
#define CFG_ADDR_PAT_ERR_COUNT    8                          //  Read 

//-------------------------------+---------------------------+-----------+-
// Credit-Val/Rdy Adapters       |  Addr                     |   Type    |
//-------------------------------+---------------------------+-----------+-
#define CFG_ADDR_GO               9                          //  Write   
#define CFG_ADDR_CLK_DIV_FACTOR   10                         //  Write 
#define CFG_ADDR_CLK_DIV_SKEW     11                         //  Write 

//-------------------------------+---------------------------+-----------+-
// CRC                           |  Addr                     |   Type    |
//-------------------------------+---------------------------+-----------+-
#define CFG_ADDR_CRC_ERROR_BIT    12                         //  Read 

//-------------------------------+---------------------------+-----------+-
// REPAIR                        |  Addr                     |   Type    |
//-------------------------------+---------------------------+-----------+-
#define CFG_ADDR_UP_REPAIR_SEL    13                         //  Write 
#define CFG_ADDR_DOWN_REPAIR_SEL  14                         //  Write 

//-------------------------------+---------------------------+-----------+-
// DEBUG COUNTERS                |  Addr                     |   Type    |
//-------------------------------+---------------------------+-----------+-
#define CFG_ADDR_DBG_TICK_COUNT     15                       //  Read
#define CFG_ADDR_DBG_NEXT_CRED_CNT  16                       //  Read
#define CFG_ADDR_DBG_CRED_RST_DELAY 17                       //  Read


//=========================================================================
// Configuration Register Default Values
//=========================================================================

//-------------------------------+-----------------------------------------
// Loopback                      |  Value  
//-------------------------------+-----------------------------------------
#define CFG_DEF_LOOPBACK          0

//-------------------------------+-----------------------------------------
// Pattern Gen & Chk             |  Value  
//-------------------------------+-----------------------------------------
#define CFG_DEF_PAT_BYPASS        0
#define CFG_DEF_PATTERN_MODE      0
#define CFG_DEF_PATTERN_1         0xAA
#define CFG_DEF_PATTERN_2         0x55   
#define CFG_DEF_PATTERN_EMPTY     0

#define CFG_DEF_PATTERN_STATE     0
#define CFG_DEF_PAT_ERR_COUNT     0

//-------------------------------+-----------------------------------------
// Credit-Val/Rdy Adapters       |  Value  
//-------------------------------+-----------------------------------------
#define CFG_DEF_GO                0
#define CFG_DEF_CLK_DIV_FACTOR    1
#define CFG_DEF_CLK_DIV_SKEW      0

//-------------------------------+-----------------------------------------
// CRC                           |  Value
//-------------------------------+-----------------------------------------
#define CFG_DEF_CRC_ERROR_BIT     0

//-------------------------------+-----------------------------------------
// REPAIR                        |  Value
//-------------------------------+-----------------------------------------
#define CFG_DEF_UP_REPAIR_SEL     0
#define CFG_DEF_DOWN_REPAIR_SEL   0

//-------------------------------+-----------------------------------------
// DEBUG COUNTERS                |  Value
//-------------------------------+-----------------------------------------
#define CFG_DEF_DBG_TICK_COUNT     0
#define CFG_DEF_DBG_NEXT_CRED_CNT  0
#define CFG_DEF_DBG_CRED_RST_DELAY 0

// Msg formatting macros
#define BRGTC6_MK_CNFG_MSG(addr, value) \
    (((CNFG_MSG & 0x1) << (BRGTC6_ADDR_WIDTH + BRGTC6_CNFG_WIDTH)) | \
    ((addr & ((1U << BRGTC6_ADDR_WIDTH) - 1)) << BRGTC6_CNFG_WIDTH) | \
    (value & ((1U << BRGTC6_CNFG_WIDTH) - 1)))

#define BRGTC6_MK_CHNL_MSG(value) \
    ((CHNL_MSG & 0x1) << (BRGTC6_CNFG_WIDTH)) | \
    (value & ((1U << BRGTC6_CNFG_WIDTH) - 1))

#endif