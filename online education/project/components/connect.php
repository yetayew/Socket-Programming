<?php

  $db_name = 'mysql:host=localhost:3310;dbname=onlineedu';
   $user_name = 'root';
   $user_password = 'root';

   $conn = new PDO($db_name, $user_name, $user_password);

   function unique_id() {
      $str = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890';
      $rand = array();
      $length = strlen($str) - 1;
      for ($i = 0; $i < 20; $i++) {
          $n = mt_rand(0, $length);
          $rand[] = $str[$n];
      }
      return implode($rand);
   }



// $conn = mysqli_connect('localhost:3310', 'root', 'root','course_db');
//
//
// if(mysqli_connect_errno()){
//   echo "Failed to connect to MySQL".mysqli_connect_errno();
// }


?>
