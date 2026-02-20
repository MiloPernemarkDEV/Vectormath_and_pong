using UnityEngine;
 
 public class PaddleController : MonoBehaviour
 {
     public float speed = 10f;
     public bool isPlayerOne;
 
     private PongVector.Vec2 position;
 
     void Start()
     {
         position.x = transform.position.x;
         position.y = transform.position.y;
     }
 
     void Update()
     {
         float input = 0;
 
         if (isPlayerOne)
         {
             if (Input.GetKey(KeyCode.W)) input = 1;
             if (Input.GetKey(KeyCode.S)) input = -1;
         }
         else
         {
             if (Input.GetKey(KeyCode.UpArrow)) input = 1;
             if (Input.GetKey(KeyCode.DownArrow)) input = -1;
         }
 
         PongVector.Vec2 move;
         move.x = 0;
         move.y = input * speed * Time.deltaTime;
 
         position = PongVector.v2_add(position, move);
 
         transform.position = new Vector3(position.x, position.y, 0);
     }
 }