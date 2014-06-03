using UnityEngine;
using System.Collections;

public class Entity : MonoBehaviour {

	public string[]   varArray = new string[4];
	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}
	
	public string ParseEntity()
	{
		string entityData;
        entityData = varArray[0] + "|" + this.transform.position.x + "|" + this.transform.position.y + "|" + this.transform.position.z + "|";
		for (int i = 1; i < varArray.Length; i++)
		{
			entityData+= varArray[i] + "|";
		}
		
		return entityData;
	}
}
