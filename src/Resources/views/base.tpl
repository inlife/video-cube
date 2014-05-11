<!DOCTYPE html>
<html>
	<head lang="en">
		<meta charset="utf-8" />
		<link href="css/style.css" rel="stylesheet" />
		<script src="js/jquery.js"></script>
		<script src="js/init.js"></script>
	</head>
	<body>
		<header>
			<div class="wrapper">
				<div class="logo"></div>
				<a href="{{baseurl}}">
					<h1>VideoCube</h1>
					<span>Your videos are here. Redefined.</span>
				</a>
				<a href="{{baseurl}}?name=user" class="button">Enter</a>
			</div>
		</header>
		<nav>
			<!--div class="wrapper">
				<a href="#">All videos</a>
				<a href="#">Likes</a>
				<a href="#">Profile</a>
			</div-->
		</nav>
		<main>
			<div class="wrapper">
				<article>
				{{content}}
				</article>
			</div>
		</main>
	<script src="js/opt.js"></script>
	</body>
</html>