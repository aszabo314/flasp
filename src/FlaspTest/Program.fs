// Learn more about F# at http://fsharp.org
// See the 'F# Tutorial' project for more help.

open Flasp



[<EntryPoint>]
let main argv = 
    
    Flasp.test()
    
    printfn "%A" argv
    0 // return an integer exit code
