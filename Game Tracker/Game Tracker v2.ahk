#NoEnv  ; Recommended for performance and compatibility with future AutoHotkey releases.
; #Warn  ; Enable warnings to assist with detecting common errors.
SendMode Input  ; Recommended for new scripts due to its superior speed and reliability.
SetWorkingDir %A_ScriptDir%  ; Ensures a consistent starting directory.
#SingleInstance, force
#NoTrayIcon

       FINAL_FREQUENCY := 25 ; mins
global FINAL_PLAY_SOUND := true
global PLAYER_THRESHOLD := 3


 ; FORMAT: Server("<SERVER NAME>", "<IP:PORT>", <# of BOTS ON SERVER>)
global Servers := {new Server("KarmaMG", "172.93.101.24:27029"): 0
                  ,new Server("Time2KillMG", "209.222.101.155:27042"): 0
                  ,new Server("SwooblesMG", "199.60.101.60:27015"): 0
                  ,new Server("ExoticMG", "51.89.235.154:27015"): 0
                  ,new Server("TheWalkingMG", "164.132.201.159:27125", 2): 0}






global prompt := false
freq := FINAL_FREQUENCY * 60000
SetTimer, check, %freq%

check(bool := false) {
    process, exist, csgo.exe
    if (!errorlevel) {
        For k, v in Servers ; put servers in dict
            Servers[k] := k.getPlayers()
        out := StrSplit(Arr2Str(sort(Servers)), "`n") ; sort

        global serv1 := Server.getServer(Servers, SubStr(out[1], 1, InStr(out[1], ":")-1))
        global serv2 := Server.getServer(Servers, SubStr(out[2], 1, InStr(out[2], ":")-1))
        global serv3 := Server.getServer(Servers, SubStr(out[3], 1, InStr(out[3], ":")-1))

        out := limit("1)" out[1] " " serv1.getMap()) "`n" limit("2)" out[2] " " serv2.getMap()) "`n" limit("3)" out[3] " " serv3.getMap())

        if (SubStr(out, InStr(out, ": ")+2, 1) >= PLAYER_THRESHOLD or bool) {
            if (FINAL_PLAY_SOUND)
                SoundPlay, %A_WinDir%\Media\Windows Battery Low.wav, 1
            OSDTIP_Pop("Game Tracker | (Alt + num) to join", out, -10000, "CW424549 CTffffff", , 245)
            prompt := true
        }
        Sleep, 10000
        prompt := false
    }
}

sort(Arr) {
    tmp := {}
    for key, val in Arr
        tmp[val] ? tmp[val].Insert(key) : tmp[val] := [key]
    return tmp
}

Arr2Str(arr) {
    out:=""
    for i, x in arr 
        for k, y in x
            out .= y.getName() ": " i "`n"
    out := RegExReplace(StringReverse(out, "`n"),"^(\n*?)","")
    return SubStr(out, 1, InStr(out, "`n", false, 1, 3))
}

limit(output) {
  return StrReplace(StrReplace(Trim(SubStr(output, 1, 39)), "_", ""), "`n", "")
}

Class Server {

    __New(name := "NA", ip := "NA", bots := 0) {
        this.name := name
        this.ip := ip
        this.bots := bots
        this.url := "https://www.gametracker.com/server_info/" ip
        this.playercount := 0
    }

    getPlayers() {
        whr := ComObjCreate("WinHttp.WinHttpRequest.5.1")
        Whr.Open("GET", this.url, true)
        Whr.Send()
        Whr.WaitForResponse()
        Arr := Whr.responseBody()
        pData := NumGet(ComObjValue(arr) + 8 + A_PtrSize)
        length := arr.MaxIndex() + 1
        aab := StrGet(pData, length, "UTF-8")
        out := SubStr(aab, InStr(aab, "HTML_num_players")+18, 1)
        return (out + 0 >= 0) ? out-this.bots : 0
    }

    getMap() {
        whr := ComObjCreate("WinHttp.WinHttpRequest.5.1")
        Whr.Open("GET", this.url, true)
        Whr.Send()
        Whr.WaitForResponse()
        Arr := Whr.responseBody()
        pData := NumGet(ComObjValue(arr) + 8 + A_PtrSize)
        length := arr.MaxIndex() + 1
        aab := StrGet(pData, length, "UTF-8")
        out := SubStr(aab, InStr(aab, "HTML_curr_map")+20, InStr(SubStr(aab, InStr(aab, "HTML_curr_map")+20), "`n"))
        return (InStr(out, "xmlns") > 0) ? "Offline" : out

    }

    getName() {
        return this.name
    }

    join() {
        Run % "steam://connect/" this.ip
    }

    getServer(servers, name) {
      for k, v in servers {
        if (k.getName() = name)
          return k
      }
    }
}

OSDTIP_Pop(P*) { ; OSDTIP_Pop v0.55 by SKAN on D361/D36E @ tiny.cc/osdtip 
 Local
 Static FN:="", ID:=0, PM:="", PS:="" 
 
   If !IsObject(FN)
     FN := Func(A_ThisFunc).Bind(A_ThisFunc) 
 
   If (P.Count()=0 || P[1]==A_ThisFunc) {
     OnMessage(0x202, FN, 0),  OnMessage(0x010, FN, 0)                   ; WM_LBUTTONUP, WM_CLOSE 
     SetTimer, %FN%, OFF
     DllCall("AnimateWindow", "Ptr",ID, "Int",200, "Int",0x50004)        ; AW_VER_POSITIVE | AW_SLIDE
     Progress, 10:OFF                                                    ; | AW_HIDE
     Return ID:=0
   }
 
   MT:=P[1], ST:=P[2], TMR:=P[3], OP:=P[4], FONT:=P[5] ? P[5] : "Lucida Sans Typewriter"
   Title := (TMR=0 ? "0x0" : A_ScriptHwnd) . ":" . A_ThisFunc
   
   If (ID) {
     Progress, 10:, % (ST=PS ? "" : PS:=ST), % (MT=PM ? "" : PM:=MT), %Title%
     OnMessage(0x202, FN, TMR=0 ? 0 : -1)                                ; v0.55
     SetTimer, %FN%, % Round(TMR)<0 ? TMR : "OFF" 
     Return ID
   }                                                                                                        
 
   If ( InStr(OP,"U2",1) && FileExist(WAV:=A_WinDir . "\Media\Windows Notify.wav") )
     DllCall("winmm\PlaySoundW", "WStr",WAV, "Ptr",0, "Int",0x220013)    ; SND_FILENAME | SND_ASYNC   
                                                                         ; | SND_NODEFAULT   
   DetectHiddenWindows, % ("On", DHW:=A_DetectHiddenWindows)             ; | SND_NOSTOP | SND_SYSTEM  
   SetWinDelay, % (-1, SWD:=A_WinDelay)                            
   DllCall("uxtheme\SetThemeAppProperties", "Int",0)
   Progress, 10:C00 ZH1 FM9 FS10 CWF0F0F0 CT101010 %OP% B1 M HIDE,% PS:=ST, % PM:=MT, %Title%, %FONT%
   DllCall("uxtheme\SetThemeAppProperties", "Int",7)                     ; STAP_ALLOW_NONCLIENT
                                                                         ; | STAP_ALLOW_CONTROLS
   WinWait, %Title% ahk_class AutoHotkey2                                ; | STAP_ALLOW_WEBCONTENT
   WinGetPos, X, Y, W, H                                                 
   SysGet, M, MonitorWorkArea
   WinMove,% "ahk_id" . WinExist(),,% MRight-W,% MBottom-(H:=InStr(OP,"U1",1) ? H : Max(H,100)), W, H
   If ( TRN:=Round(P[6]) & 255 )
     WinSet, Transparent, %TRN% 
   ControlGetPos,,,,H, msctls_progress321       
   If (H>2) {
     ColorMQ:=Round(P[7]),  ColorBG:=P[8]!="" ? Round(P[8]) : 0xF0F0F0,  SpeedMQ:=Round(P[9])
     Control, ExStyle, -0x20000,        msctls_progress321               ; v0.55 WS_EX_STATICEDGE
     Control, Style, +0x8,              msctls_progress321               ; PBS_MARQUEE
     SendMessage, 0x040A, 1, %SpeedMQ%, msctls_progress321               ; PBM_SETMARQUEE
     SendMessage, 0x0409, 1, %ColorMQ%, msctls_progress321               ; PBM_SETBARCOLOR
     SendMessage, 0x2001, 1, %ColorBG%, msctls_progress321               ; PBM_SETBACKCOLOR
   }  
   DllCall("AnimateWindow", "Ptr",WinExist(), "Int",200, "Int",0x40008)  ; AW_VER_NEGATIVE | AW_SLIDE
   SetWinDelay, %SWD%
   DetectHiddenWindows, %DHW%
   If (Round(TMR)<0)
     SetTimer, %FN%, %TMR%
   OnMessage(0x202, FN, TMR=0 ? 0 : -1),  OnMessage(0x010, FN)           ; WM_LBUTTONUP,  WM_CLOSE
 Return ID:=WinExist()
}

StringReverse(str, Separator="", OmitChars="") {   ; A|B|CD --> CD|B|A
   Loop,Parse,% StrReplace(str,Separator,(BS:=chr(8))),%BS%,%OmitChars%
      i := A_LoopField (a_index=1 ? "" : BS i)
   Return StrReplace(i, BS, Separator)
}

!1::
  if (prompt) {
    tooltip % "Joining " serv1.getName() 
    serv1.join()
    prompt := false
    Sleep, 3000
    tooltip
  }
  Else
    Send, !3
Return

!2::
  if (prompt) {
    tooltip % "Joining " serv2.getName() 
    serv2.join()
    prompt := false
    Sleep, 3000
    tooltip
  }
  Else
    Send, !3
Return

!3::
  if (prompt) {
    tooltip % "Joining " serv3.getName() 
    serv3.join()
    prompt := false
    Sleep, 3000
    tooltip
  }
  Else
    Send, !3
Return

!9::
  check(true)
Return