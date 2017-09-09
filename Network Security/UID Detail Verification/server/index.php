<!--A Design by W3layouts
Author: W3layout
Author URL: http://w3layouts.com
License: Creative Commons Attribution 3.0 Unported
License URL: http://creativecommons.org/licenses/by/3.0/
-->
<!DOCTYPE HTML>
<html>
<head>
<title>UID Verification</title>
<meta name="viewport" content="width=device-width, initial-scale=1">
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<meta name="keywords" content="Tourists Reservation Form template Responsive, Login form web template,Flat Pricing tables,Flat Drop downs Sign up Web Templates, 
 Flat Web Templates, Login sign up Responsive web template, SmartPhone Compatible web template, free web designs for Nokia, Samsung, LG, SonyEricsson, Motorola web design">
<script type="application/x-javascript"> addEventListener("load", function() { setTimeout(hideURLbar, 0); }, false); function hideURLbar(){ window.scrollTo(0,1); } </script>
<!-- jQuery (necessary for Bootstrap's JavaScript plugins) -->
<!-- Custom Theme files -->
<link href="css/font-awesome.css" rel="stylesheet"> 
<link href="css/wickedpicker.css" rel="stylesheet" type='text/css' media="all" />
<link href="css/style.css" rel='stylesheet' type='text/css' />
<!--fonts--> 
<link href="//fonts.googleapis.com/css?family=Roboto:300,400,500,700" rel="stylesheet">
<link href="//fonts.googleapis.com/css?family=Montserrat:400,700" rel="stylesheet">


<!--//fonts--> 
</head>
<body>
<!--background-->
<h1> UID Details Verification Form </h1>
<div id="dwnlds">
   <h2>Downloads</h2></br>
   
   <div id=dwnl  align="left">
   <a href="public_key.pem" download>Public Key Certificate</a></br></br>
   <a href="client.zip" download>Executable to verify server response</a>
   </div>
   </div>
    <div class="bg-agile">
	<div class="book-reservation">
			<form action="post.php" method="post">
					<div class="form-date-w3-agileits">
						<label><i class="fa fa-user" aria-hidden="true"></i> UID :</label>
						<input type="text" name="uid" placeholder="Your  aadhar Card number" required=""/>
					</div>
					<div class="form-date-w3-agileits">
						<label><i class="fa fa-user" aria-hidden="true"></i>Name :</label>
						<input type="text" name="name" placeholder="Your name"/>
					</div>
					<div class="form-date-w3-agileits">
						<label><i class="fa fa-calendar" aria-hidden="true"></i>Date of Birth:</label>
						<input  id="datepicker2" name="dob" type="text" value="mm/dd/yyyy" onfocus="this.value = '';" onblur="if (this.value == '') {this.value = 'mm/dd/yyyy';}">
					</div>
					<div class="form-date-w3-agileits">
						<label><i class="fa fa-user" aria-hidden="true"></i>Father's Name :</label>
						<input type="text" name="fname" placeholder="Your father's name"/>
					</div>

					<div class="clear"> </div>
					<div class="make">
						  <input type="submit" value="Submit">
					</div>
			</form>
	</div>
	
   </div>
   
   
   <!--copyright-->
			<div class="copy w3ls">
		       <p>Copyright 2017 UID Detail Verification  | by <a href="https://india.gov.in/" target="_blank">Government of India</a> </p>
	        </div>
		<!--//copyright-->
		<script type="text/javascript" src="js/jquery-2.1.4.min.js"></script>
		<script type="text/javascript" src="js/wickedpicker.js"></script>
			<script type="text/javascript">
				$('.timepicker').wickedpicker({twentyFour: false});
			</script>


		<!-- Calendar -->
				<link rel="stylesheet" href="css/jquery-ui.css" />
				<script src="js/jquery-ui.js"></script>
				  <script>
						  $(function() {
							$( "#datepicker,#datepicker1,#datepicker2,#datepicker3" ).datepicker();
						  });
				  </script>
			<!-- //Calendar -->
			

</body>
</html>