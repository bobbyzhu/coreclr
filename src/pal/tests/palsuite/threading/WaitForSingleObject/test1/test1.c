//
// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information. 
//

/*============================================================
**
** Source: test1.c 
**
** Purpose: Test for WaitForSingleObjectTest. Create two events, one
** with a TRUE and one with FALSE intial state.  Ensure that WaitForSingle
** returns correct values for each of these.
**
**
**=========================================================*/

#include <palsuite.h>

BOOL WaitForSingleObjectTest()
{

    BOOL bRet = FALSE;
    DWORD dwRet = 0;

    LPSECURITY_ATTRIBUTES lpEventAttributes = 0;
    BOOL bManualReset = TRUE; 
    BOOL bInitialState = TRUE;
    LPCTSTR lpName = "Event #6";

    HANDLE hEvent;

    /* Create an event, and ensure the HANDLE is valid */
    hEvent  = CreateEvent(lpEventAttributes, bManualReset, 
                          bInitialState, lpName); 

    if (hEvent != INVALID_HANDLE_VALUE)
    {
        
        /* Call WaitForSingleObject with 0 time on the event.  It
           should return WAIT_OBJECT_0
        */
        
        dwRet = WaitForSingleObject(hEvent,0);
    
        if (dwRet != WAIT_OBJECT_0)
        {
            Trace("WaitForSingleObjectTest:WaitForSingleObject %s "
                   "failed (%x)\n",lpName,GetLastError());
        }
        else
        {
            bRet = CloseHandle(hEvent);
        
            if (!bRet)
            {
                Trace("WaitForSingleObjectTest:CloseHandle %s "
                       "failed (%x)\n",lpName,GetLastError());
            }
        }
    }
    else
    {
        Trace("WaitForSingleObjectTest:CreateEvent %s "
               "failed (%x)\n",lpName,GetLastError());
    }
    
    /* If the first section passed, Create another event, with the
       intial state being FALSE this time.
    */

    if (bRet)
    {
        bRet = FALSE;

        bInitialState = FALSE;

        hEvent = CreateEvent( lpEventAttributes, 
                              bManualReset, bInitialState, lpName); 
 
        if (hEvent != INVALID_HANDLE_VALUE)
        {
            
            /* Test WaitForSingleObject and ensure that it returns
               WAIT_TIMEOUT in this case.
            */
            
            dwRet = WaitForSingleObject(hEvent,0);

            if (dwRet != WAIT_TIMEOUT)
            {
                Trace("WaitForSingleObjectTest:WaitForSingleObject %s "
                       "failed (%x)\n",lpName,GetLastError());
            }
            else
            {
                bRet = CloseHandle(hEvent);

                if (!bRet)
                {
                    Trace("WaitForSingleObjectTest:CloseHandle %s failed "
                           "(%x)\n",lpName,GetLastError());
                }
            }
        }
        else
        {
            Trace("WaitForSingleObjectTest::CreateEvent %s failed "
                   "(%x)\n",lpName,GetLastError());
        }
    }
    return bRet;
}

int __cdecl main(int argc, char **argv)
{
    if(0 != (PAL_Initialize(argc, argv)))
    {
        return ( FAIL );
    }
        
    if(!WaitForSingleObjectTest())
    {
        Fail ("Test failed\n");
    }
        
    PAL_Terminate();
    return ( PASS );

}
