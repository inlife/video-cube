/* 
$(function () {
	$("a").click(function(e) { 
		e.preventDefault(); 
	});

	function Scroll() {
		var wnd = $(window).scrollTop();
		if (wnd >= 250) {
			$("header").css({"background-attachment":"inherit"});
			console.log("yep");
		} else {
			$("header").css({"background-attachment":"fixed"});
		}
	}
	$(window).scroll(function() {
    	Scroll();
	});
});

*/

$("input:file").click(function(element) {
		$(".upload").css("background-image", "../img/icon-OK.svg")
})
