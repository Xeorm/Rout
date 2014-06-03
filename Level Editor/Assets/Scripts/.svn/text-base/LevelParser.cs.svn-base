using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System.IO;

public class LevelParser : MonoBehaviour {

	public string fileName = "";
    private GameObject[] objs;
	// Use this for initialization
	void Start () {

        objs = (GameObject[])FindSceneObjectsOfType(typeof(GameObject));
		
		using (StreamWriter sw = File.CreateText(fileName))
		{
            for (int i = 0; i < objs.Length; i++)
            {
                Entity entity = (objs[i].GetComponent("Entity")as Entity);
                if (entity != null)
                {
                    sw.WriteLine(entity.ParseEntity());
                }
            }
			sw.Close();
		}
	}
	
	// Update is called once per frame
	void Update () {
	
	}
}
