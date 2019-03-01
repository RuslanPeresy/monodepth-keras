using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class WebCamRenderer : MonoBehaviour
{
    public WebCamTexture webcamTexture;

    // Start is called before the first frame update
    void Start()
    {
        WebCamDevice[] devices = WebCamTexture.devices;
        if (devices.Length == 0)
        {
            Debug.Log("No camera detected");
            return;
        }

        webcamTexture = new WebCamTexture(devices[0].name, 320, 240);
        webcamTexture.Play();

        this.GetComponent<RawImage>().texture = webcamTexture;
    }
}
