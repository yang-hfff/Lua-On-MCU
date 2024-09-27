/*************************************************************
 * Copyright (C) 2024-09-27 Yang Haifeng. All rights reserved.
 *
 * This code is licensed under the MIT license
 *************************************************************/
#ifndef __LOGS_H
#define __LOGS_H


/*------config area start------*/

#define USE_LOG         1

#define USE_COLR_MODE   0

#define LOG_PRINT       printf

/*------config area end------*/





#if USE_COLR_MODE
    #define COLR_SET(dis_mode,fwd_clor,bak_clor) printf("\033["#dis_mode";"#fwd_clor";"#bak_clor"m")
#else 
    #define COLR_SET(dis_mode,fwd_clor,bak_clor) (void)0
#endif

#if USE_LOG == 1  
    /*---general log---*/
    #define LOG_E(fmt,...)  COLR_SET(0,31,40),\
                            LOG_PRINT("[ERROR ][%s:%d][%s]"fmt,__FILE__,__LINE__,__FUNCTION__,##__VA_ARGS__),\
                            COLR_SET(0,0,0)
    #define LOG_W(fmt,...)  COLR_SET(0,33,40),\
                            LOG_PRINT("[WARN  ][%s:%d][%s]"fmt,__FILE__,__LINE__,__FUNCTION__,##__VA_ARGS__),\
                            COLR_SET(0,0,0)
    #define LOG_I(fmt,...)  COLR_SET(0,36,40),\
                            LOG_PRINT("[INFO  ][%s:%d][%s]"fmt,__FILE__,__LINE__,__FUNCTION__,##__VA_ARGS__),\
                            COLR_SET(0,0,0)
    #define LOG_D(fmt,...)  COLR_SET(0,32,40),\
                            LOG_PRINT("[DEBUG ][%s:%d][%s]"fmt,__FILE__,__LINE__,__FUNCTION__,##__VA_ARGS__),\
                            COLR_SET(0,0,0)
                            
                            
    /*---expanded log---*/
    #define LOG_F(fmt,...)  COLR_SET(0,35,40),\
                            LOG_PRINT("[FATAL ][%s:%d][%s]"fmt,__FILE__,__LINE__,__FUNCTION__,##__VA_ARGS__),\
                            COLR_SET(0,0,0)
    #define LOG_V(fmt,...)  COLR_SET(0,34,40),\
                            LOG_PRINT("[VERBO ][%s:%d][%s]"fmt,__FILE__,__LINE__,__FUNCTION__,##__VA_ARGS__),\
                            COLR_SET(0,0,0)                       
#else
    #define LOG_E(fmt,...)  (void)0    
    #define LOG_W(fmt,...)  (void)0    
    #define LOG_I(fmt,...)  (void)0   
    #define LOG_D(fmt,...)  (void)0        
    #define LOG_F(fmt,...)  (void)0   
    #define LOG_V(fmt,...)  (void)0    
#endif



#endif /*__LOGS_H*/




