namespace Flasp

open System
open System.Runtime.InteropServices

module Native =
    
    [<Literal>]
    let lib = @"FlaspNative"

    [<DllImport(lib)>]
    extern void testEverything()

module Flasp =
    
    let test () =
        Native.testEverything()