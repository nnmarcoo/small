#SingleInstance, force
Gui,+AlwaysOnTop
Gui, Add, Edit, x12 y10 w326 h40 vpEdit,
Gui, Add, Text, x12 y50 w320 h80 vpText
Gui, Add, Edit, x12 y130 w326 h130, This area is a notepad!`n`nLC-3 Instruction Converter`nmade by Marco Todorov`nVersion 0.0.2
Gui, Show, x127 y87 h275 w350, LC-3 Instruction Converter 0.0.2
SetTimer, check, 250
Return

check:
    gui,submit,nohide ;updates gui variable
    guicontrol,,pText,% convert(pEdit)
return

GuiClose:
ExitApp

convert(input) {
    instruct := RegExReplace(input, "[ \n\t]")
    if (strLen(instruct) > 16)
        return "`nInvalid Length"
    if (RegExReplace(instruct, "[01]") > 0)
        return "`nNot binary"

    opCodeKey := {"0001":"ADD                 DR = SR1 + SR2 || DR = SR1 + imm5a","0101":"AND                 DR = SR1 && SR2 || DR = SR1 && imm5b","1001":"NOT                 DR = ~SRc","0000":"BR                 PC = [PC + 1 + PCoffset9]d","1100":"JMP                 PC = BaseRe","0110":"LDR                 DR = mem[BaseR + offset6]f","0111":"STR                 mem[BaseR + offset6] = SRg","0010":"LD                 DR = mem[PC + 1 + PCoffset9]h","0011":"ST                 mem[PC + 1 + PCoffset9] = SRi","1010":"LDI                 DR = mem[mem[PC + 1 + PCoffset9]]j","1011":"STI                 mem[mem[PC + 1 + PCoffset9]] = SRk","1110":"LEA                 DR = [PC + 1 + PCoffset9]l","1111":"TRAP                 m"}

    opCode := SubStr(opCodeKey[SubStr(instruct, 1, 4) ""], 1, StrLen(opCodeKey[SubStr(instruct, 1, 4) ""]) - 1)
    opCodeIndex := Asc(SubSTr(opCodeKey[SubStr(instruct, 1, 4) ""], StrLen(opCode) + 1)) - 96


    if (opCodeIndex <= 2) { ; ADD/AND
        if (SubStr(instruct, 11, 1) == "0")
            SR2 := SubStr(instruct, 14)
        else
            imm5 := SubStr(instruct, 12)
        DR := SubStr(instruct, 5, 3)
        SR1 := SubStr(instruct, 8, 3)
    }
    else if (opCodeIndex == 3) { ; NOT
        DR := SubStr(instruct, 5, 3)
        SR1 := SubStr(instruct, 8, 3)
    }
    else if (opCodeIndex == 4) { ; BR
        PCoffset9 := SubStr(instruct, 8)
        NZP := SubStr(instruct, 5, 3)
    }
    else if (opCodeIndex == 5) ; JMP
        BaseR := SubStr(instruct, 12, 3)
    else if (opCodeIndex <= 7) { ; LDR/STR
        if (opCodeIndex == 6)
            DR := SubStr(instruct, 5, 3) ; LDR
        else
            SR1 := SubStr(instruct, 5, 3) ; STR
        BaseR := SubStr(instruct, 8, 3)
        offset6 := SubStr(instruct, 11)
    }
    else if (opCodeIndex <= 12){
        if (opCodeIndex == 9 || opCodeIndex == 11) ; ST/STI
            SR1 := SubStr(instruct, 5, 3)
        else ;                                     ; LD/LDI/LEA
            DR := SubStr(instruct, 5, 3)
        PCOffset9 := SubStr(instruct, 8)
    }
    else {
        if (SubStr(instruct, 5, 4) != "0000")
            opCode := "UNKNOWN"
        else if (SubStr(instruct, 9) == "00100101")
            opCode .= "HALT"
        else if (SubStr(instruct, 9) == "00100011")
            opCode .= "IN"
        else if (SubStr(instruct, 9) == "00100001")
            opCode .= "OUT"
        else if (SubStr(instruct, 9) == "00100000")
            opCode .= "GETC"
        else if (SubStr(instruct, 9) == "00100010")
            opCode .= "PUTS"
        else if (SubStr(instruct, 9) == "00101000")
            opCode .= "PUTSP"
    }

    vals := {"aopCode": opCode, "bDR": DR, "cSR1": SR1, "dSR2": SR2, "eimm5": imm5, "hPCoffset9": PCOffset9, "fBaseR": BaseR, "goffset6": offset6, "hNZP": NZP}

    for k, v in vals {
        if (v != "")
            out .= "`n" subStr(k, 2) ": " v
    }
    return out
}