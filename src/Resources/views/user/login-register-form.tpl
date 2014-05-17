<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8" />
	<link href="css/login.css" rel="stylesheet" />
</head>
<body>
	<div id="wrapper" class="form-container">
		<h1>{{message}}</h1>
		<div class="login-block">
			<div class="header">
				<span>LOG IN</span>
			</div>
			<div class="form">
				<form action="{{baseurl}}?name=user&action=login" method="post">
					<!--div class="button facebook">
						<img src="http://imageshack.com/a/img716/8297/66tc.png" alt="facebook">
					</div>
					<p>OR</p-->
					<p></p>
					<input type="email" name="login" placeholder="Email"> <br />
					<input type="password" name="password" placeholder="Password" /> 
					<input type="submit" class="button submit" value="I'M READY">
				</form>
			</div>
		</div>
		<div class="register-block">
			<div class="header">
				<span>REGISTER</span>
			</div>
			<div class="form">
				<form action="{{baseurl}}?name=user&action=register" method="post">
					<!--div class="button facebook">
						<img src="http://imageshack.com/a/img716/8297/66tc.png" alt="facebook">
					</div>
					<p>OR</p-->
					<p></p>
					<input type="email" name="login" placeholder="Email"> <br />
					<input type="password" name="password" placeholder="Password" />  <br />
					<input type="password" name="repassword" placeholder="Password" /> 
					<input type="submit" class="button submit" value="GO">
				</form>
			</div>
		</div>
	</div>
</body>
</html>