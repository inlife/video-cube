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
				<a href="{{baseurl}}?name=videos&action=likes">Likes</a>
				<a href="{{baseurl}}?name=videos&action=recommend">Recommendations</a>
				<a href="{{baseurl}}?name=user">Profile</a>
			</div>
		</nav>
		<main>
			<div class="wrapper">
				<article class="video">
					<div class="line">
						<div class="block">
							<div class="artwork"><iframe width="640" height="360" src="//www.youtube.com/embed/xjtWUX37RPY" frameborder="0" allowfullscreen></iframe></div>
							<span><h2><a href="#">{{title}}</a></h2></span>
							<div class="like"><a href="#" class="button">Мне понравилось</a></div>
						</div>
						<div class="block sidebar">
							<h3>Похожие видео</h3>
							<ul class="video-list">
								<li><img src="{{baseurl}}{{preview}}" class="small-artwork" />
									<a href="{{baseurl}}?name=video&action=index&id={{videoid}}">{{title}}</a>
								</li>

								<li><img src="{{baseurl}}{{preview}}" class="small-artwork" />
									<a href="{{baseurl}}?name=video&action=index&id={{videoid}}">{{title}}</a>
								</li>

								<li><img src="{{baseurl}}{{preview}}" class="small-artwork" />
									<a href="{{baseurl}}?name=video&action=index&id={{videoid}}">{{title}}</a>
								</li>

								<li><img src="{{baseurl}}{{preview}}" class="small-artwork" />
									<a href="{{baseurl}}?name=video&action=index&id={{videoid}}">{{title}}</a>
								</li>
							</ul>
						</div>
					</div>
				</article>
			</div>
		</main>
	<script src="sc/opt.js"></script>
	</body>
</html>