<!DOCTYPE html>
<html>
	<head lang="en">
		<meta charset="utf-8" />
		<link href="css/style.css" rel="stylesheet" />
	</head>
	<body>
		<header>
			<div class="wrapper">
				<div class="logo"></div>
				<a href="#">
					<h1>VideoCube</h1>
					<span>Your videos are here. Redefined.</span>
				</a>
				<a href="#" class="button">Enter</a>
			</div>
		</header>
		<nav>
			<div class="wrapper">
				<a href="#">All videos</a>
				<a href="#">Likes</a>
				<a href="#">Profile</a>
			</div>
		</nav>
		<main>
			<div class="wrapper">
				<article class="video add">
					<div class="line">
						<h3>Добавление видео</h3>
						<form id="fileinfo" enctype="multipart/form-data" method="post" name="fileinfo">
							<input type="text" id="title" name="title" placeholder="Add title" />
							<div class="preview">
								<div class="upload"><input type="file" name="file" required /></div>
							</div>
						</form>
						<input type="submit" value="Add video" />
					</div>
				</article>
			</div>
		</main>
	<script src="js/jquery.js"></script>
	<script src="js/opt.js"></script>
	<script src="js/upload_demo.js"></script>
	<script type="text/javascript">
		$(document).ready(function () {
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
			    		window.location.replace("{{basurl}}?name=video&action=index&id=" + data);
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
		});
	</script>
	</body>
</html>