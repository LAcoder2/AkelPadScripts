Sub PrintLog(value, bClear)
    Dim strValue
    ' Преобразуем значение в строку в зависимости от его типа
    Select Case TypeName(value)
    Case "String"
        strValue = value
    Case "Double", "Boolean", "Long", "Integer", "Byte", "Currency"
        strValue = CStr(value)
        'WScript.Echo(vartype(Array(1, 2, 3)))
    Case "Variant()"
        Dim i
        For i = 0 To UBound(value)
            strValue = strValue & value(i)
        Next
    Case Else
        On Error Resume Next
        strValue = value
        On Error GoTo 0
    End Select
    
    ' Выводим в лог с новой строки (режим добавления 2)
    ' Параметр 4 = MT_LOADFONT (использовать шрифт редактора) + MT_NOCRLF (обработка переноса)
    Dim flag
    If bClear = True Then 
        flag = 0
    Else
        flag = 2
    end if
    'AkelPad.Call "Log::Output", 4, "adfa", -1, 0
    AkelPad.Call "Log::Output", 4, strValue, -1, flag
End Sub

