<article class="video add user">
	<div class="line">
		<img src="img/userpic.jpg" class="userpic" />
		<h3>Welcome, {{userlogin}}</h3>
		<a href="{{baseurl}}?name=video&action=add"><input type="submit" value="Add video"></a>
		<a href="{{baseurl}}?name=user&action=logout"><input type="submit" value="Exit"></a>
	</div>
</article>
<article>
	{{videos}}
</article>