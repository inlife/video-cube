<!DOCTYPE html>
<html>
	<head lang="en">
		<meta charset="utf-8" />
		<link href="css/style.css" rel="stylesheet" />
		<title>VideoCube</title>
	</head>
	<body>
		<header>
			<div class="wrapper">
				<div class="logo"></div>
				<a href="{{baseurl}}">
					<h1>VideoCube</h1>
					<span>Your videos are here. Redefined.</span>
				</a>
				<a href="{{baseurl}}?name=user&action=index" class="button">Cabinet</a>
			</div>
		</header>
		<nav>
			<div class="wrapper">
				<a href="{{baseurl}}">All videos</a>
				<a href="{{baseurl}}?name=video&action=likes">Likes</a>
				<a href="{{baseurl}}?name=video&action=recommend">Recommendations</a>
			</div>
		</nav>
		<main>
			<div class="wrapper">
				<article>
				{{content}}
				</article>
			</div>
		</main>
	<script src="js/jquery.js"></script>
	<script src="js/player.js"></script>
	<script src="js/opt.js"></script>
	<script type="text/javascript">
		$(document).ready(function () {
			
		    (function() {
				if ($("#vc-player").length > 0) {
					var player = new Player("vc-player", "{{videourl}}", {{chunks}});
					player.startVideo();
				}
			})();


			if ($("#fileinfo").length > 0) {
				var uploading = false;
				var timerid = 0;
				var iter = 0;

				function startUploading() {
					uploading = true;
					timerid = setInterval(function() {
						if (iter === 0) {$('input[type=submit]').val("."); iter = 1}
						else if (iter === 1) {$('input[type=submit]').val(".."); iter = 2}
						else if (iter === 2) {$('input[type=submit]').val("..."); iter = 0}
					}, 500);
				}

				function stopUploading() {
					uploading = false;
					clearInterval(timerid);
					$('input[type=submit]').val("Add video");
				}


			    $('input[type=submit]').on('click', function(){
			    	if (uploading) return;

			        var fd = new FormData(document.getElementById("fileinfo"));

			        window.onbeforeunload = function() {
				    	if (uploading)
				        	return "Video is still uploading, are you shure you want to stop it?";
				    }

				    startUploading();

			        $.ajax({
			            url: '{{baseurl}}?name=video&action=upload&type=ajax',  
			            type: 'POST',
			            data: fd,
			            success: function(data) {
				    		stopUploading();
				    		window.location.replace("{{baseurl}}?name=video&action=index&id=" + data);
			            }, 
					    error: function(data) {
				    		stopUploading();
					    	alert(data.responseText);
					    },
			            cache: false,
			            contentType: false,
			            processData: false
			        });
			    });
		    }
		});
	</script>
	</body>
</html>