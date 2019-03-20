using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Runtime.InteropServices;

public class MatRetriever : MonoBehaviour
{
    [DllImport("DepthToUnity")]
    private static extern void GetRawImageBytes(IntPtr data, int width, int height);

    private Texture2D tex;
    private Color32[] pixel32;

    private GCHandle pixelHandle;
    private IntPtr pixelPtr;
    
    // Start is called before the first frame update
    void Start()
    {
        InitTexture();
        gameObject.GetComponent<Renderer>().material.mainTexture = tex;
    }

    // Update is called once per frame
    void Update()
    {
        MatToTexture2D();
    }

    void InitTexture()
    {
        tex = new Texture2D(1280, 720, TextureFormat.ARGB32, false);
        pixel32 = tex.GetPixels32();
        //Pin pixel32 array
        pixelHandle = GCHandle.Alloc(pixel32, GCHandleType.Pinned);
        //Get the pinned address
        pixelPtr = pixelHandle.AddrOfPinnedObject();
    }

    void MatToTexture2D()
    {
        //Convert Mat to Texture2D
        GetRawImageBytes(pixelPtr, tex.width, tex.height);
        //Update the Texture2D with array updated in C++
        tex.SetPixels32(pixel32);
        tex.Apply();
    }

    private void OnApplicationQuit()
    {
        //Free handle
        pixelHandle.Free();
    }
}
