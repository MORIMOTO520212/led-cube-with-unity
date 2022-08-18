using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Test : MonoBehaviour
{
    public SerialHandler serialHandler;
    private static System.Text.Encoding utf8Encoding = System.Text.Encoding.UTF8;
    byte[] dt = {
        0b10000000,
        0b01000000,
        0b00100000,
        0b00010000,
        0b00001000,
        0b00000100,
        0b00000010,
        0b00000001
    };
    int i = 0;
    void Update()
    {
        byte[] send = { 0b01000000, dt[i] };
        string data = utf8Encoding.GetString(send);
        serialHandler.Write(data);

        if (i == 7) { i = 0; }
        else { i++; }
    }
}
