using UnityEngine;
using TMPro;

public class GameManager : MonoBehaviour
{
    public static GameManager Instance;

    public int player1Score;
    public int player2Score;

    public TextMeshProUGUI scoreText;
    public TextMeshProUGUI winText;

    private bool gameOver;

    void Awake()
    {
        Instance = this;
    }

    void Update()
    {
        if (gameOver && Input.GetKeyDown(KeyCode.R))
        {
            RestartGame();
        }
    }

    public void Player1Score()
    {
        if (gameOver) return;

        player1Score++;
        UpdateUI();
        CheckWin();
    }

    public void Player2Score()
    {
        if (gameOver) return;

        player2Score++;
        UpdateUI();
        CheckWin();
    }

    void CheckWin()
    {
        if (player1Score >= 5)
        {
            winText.text = "Player 1 Wins!";
            gameOver = true;
        }
        else if (player2Score >= 5)
        {
            winText.text = "Player 2 Wins!";
            gameOver = true;
        }
    }

    void UpdateUI()
    {
        scoreText.text = player1Score + " - " + player2Score;
    }

    void RestartGame()
    {
        player1Score = 0;
        player2Score = 0;
        winText.text = "";
        gameOver = false;
        UpdateUI();
    }
}