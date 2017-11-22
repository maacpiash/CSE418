using UnityEngine;
using System.Collections;
using UnityEngine.SceneManagement;

public class GameController : MonoBehaviour
{

	public GameObject hazard;
	public Vector3 spawnValues;
	public int hazardCount;
	public float spawnWait;
	public float startWait;
	public float waveWait;

	public GUIText scoreText;
	public GUIText restartText;
	public GUIText gameOverText;

	private bool gameOver;
	private bool restart;
	private int score;

	IEnumerator SpawnWaves()
	{
		yield return new WaitForSeconds (startWait);
		while (true)
		{
			for (int i = 0; i < hazardCount; i++)
			{
				Vector3 spawnPosition = new Vector3 (Random.Range (-spawnValues.x, spawnValues.x), spawnValues.y, spawnValues.z);
				Quaternion spawnRotation = Quaternion.identity;
				Instantiate (hazard, spawnPosition, spawnRotation);
				yield return new WaitForSeconds (spawnWait);
			}
			yield return new WaitForSeconds (waveWait);
			if (gameOver)
			{
				restartText.text = "Press 'R' to restart";
				restart = true;
				break;
			}
		}
	}

	void UpdateScore()
	{
		scoreText.text = "Score: " + score;
	}

	// Use this for initialization
	void Start ()
	{
		gameOver = false;
		restart = false;
		restartText.text = "";
		gameOverText.text = "";
		score = 0;
		UpdateScore ();
		StartCoroutine (SpawnWaves ());
	}

	public void AddScore(int newScoreValue)
	{
		score += newScoreValue;
		UpdateScore ();
	}
	
	public void GameOver()
	{
		gameOverText.text = "Game Over!";
		gameOver = true;
	}

	void Update()
	{
		if (restart)
			if (Input.GetKeyDown (KeyCode.R))
				SceneManager.LoadScene (SceneManager.GetActiveScene ().name);
			
	}
}
