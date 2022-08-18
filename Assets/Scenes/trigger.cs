using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class trigger : MonoBehaviour
{
    public SerialHandler serialHandler;
    private static System.Text.Encoding utf8Encoding = System.Text.Encoding.UTF8;
    int x, y, z;
    string data;

    void OnTriggerEnter(Collider collider)
    {
        y = int.Parse(transform.root.gameObject.name);
        x = int.Parse(transform.parent.gameObject.name);
        z = int.Parse(transform.gameObject.name);
        byte[] send = { (byte)(0b01000000|y), (byte)(x<<4|z) };
        Write(send);
    }

    void OnTriggerExit(Collider collider)
    {
        y = int.Parse(transform.root.gameObject.name);
        x = int.Parse(transform.parent.gameObject.name);
        z = int.Parse(transform.gameObject.name);
        byte[] send = { (byte)y, (byte)(x<<4|z) };
        Write(send);
    }

    // シリアル送信
    void Write(byte[] send)
    {
        data = utf8Encoding.GetString(send);
        serialHandler.Write(data);

    }
}