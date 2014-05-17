<article class="video add">
	<div class="line">
		<h3>Upload your video</h3>
		<form id="fileinfo" enctype="multipart/form-data" method="post" name="fileinfo">
			<input type="text" id="title" name="title" placeholder="Add title" />
			<div class="preview">
				<div class="upload"><input type="file" name="file" required /></div>
			</div>
		</form>
		<script type="text/javascript">
				window.onload = function(){
    				document.getElementById('form1').onchange = function(){
        				document.getElementById('name').innerHTML = this.value;
   					};
				};
			</script>

		<div id="name"></div>
		<input type="submit" value="Add video" />
	</div>
</article>
			

