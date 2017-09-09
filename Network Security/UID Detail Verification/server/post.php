<?php
	$username="mohd";
	$password="zerofalcon6854";
	$database="nss";
	$conn = new mysqli('localhost',$username,$password,$database);
	$script_error = '<script>
				window.location.href = "pages/error.php"
				</script>';
	$script_fwd = '<script>
				window.location.href = "pages/fwd.php"
				</script>';
	$uid="";
	$dob="";
	$name="";
	$fname="";
	if(isset($_POST['dob'])){
		$dob = $_POST['dob'];
	}
	if(isset($_POST['uid'])){
		$uid = $_POST['uid'];
	}
	if(isset($_POST['name'])){
		$name = $_POST['name'];
	}
	if(isset($_POST['fname'])){
		$fname = $_POST['fname'];
	}

	//print_r($_POST);
	$q= "SELECT * from data where ID = ?";
	$query=$conn->prepare($q);
	//$uid = 1;
	//$dob = '01/01/2017';
	//$name = 'shalini';
	//print($uid);
	//print($name);
	//print($dob);
	$query->bind_param('i', $uid);
	$query->execute();
	$result = $query->get_result();
	$row = $result->fetch_all(MYSQLI_NUM);
	//print($row[0][2]);
	if(sizeof($row)!=0){
		/*
		$myfile = fopen("make.tmp", "w") or die("Unable to open file!");
		fwrite($myfile, 'make '.$uid."\r\n");
		fclose($myfile);
		echo $script_fwd;
		*/
		
		$arr=$row[0];
		//print_r($arr);
		if($name==''){
			$name_out='Not_Given';
		}
		elseif($name==$arr[1]){
			$name_out='True';
		}
		else {
			$name_out='False';
		}
		if($dob=='mm/dd/yyyy'){
			$dob_out='Not_Given';
		}
		elseif($dob==$arr[4]){
			$dob_out='True';
		}
		else {
			$dob_out='False';
		}
		if($fname==''){
			$fname_out='Not_Given';
		}
		elseif($fname==$arr[5]){
			$fname_out='True';
		}
		else {
			$fname_out='False';
		}
		//echo $dob;
		//echo srr
		shell_exec("python C:\\xampp\\htdocs\\nss\\server.py $name_out $dob_out $fname_out");
		echo $script_fwd;
	}
	else{
		echo $script_error;
		//echo 'invalid UID';
	}
	$conn->close();
	
?>