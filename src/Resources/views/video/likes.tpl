<!DOCTYPE html>
<html>
	<head lang="en">
		<meta charset="utf-8" />
		<link href="style.css" rel="stylesheet" />
		<script src="sc/jquery.js"></script>
	</head>
	<body>
		<header>
			<div class="wrapper">
				<div class="logo"></div>
				<a href="{{baseurl}}">
					<h1>VideoCube</h1>
					<span>Your videos are here. Redefined.</span>
				</a>
				<a href="{{baseurl}}?name=user" class="button">Cabinet</a>
			</div>
		</header>
		<nav>
			<div class="wrapper">
				<a href="{{baseurl}}">All videos</a>
				<a href="{{baseurl}}?name=videos&action=recommend">Recommendations</a>
				<a href="{{baseurl}}?name=user">Profile</a>
			</div>
		</nav>
		<main>
			<div class="wrapper">
				<article class="video add user">
					<div class="line">
						<h3>Liked videos</h3>
					</div>
				</article>
				{{content}}
			</div>
		</main>
	<script src="sc/opt.js"></script>
	<script src="sc/upload_demo.js"></script>
	</body>
</html>