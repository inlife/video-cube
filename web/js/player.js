  
    
// usage:    
// var player = new Player('videoDiv', 1,36);
// player.startVideo();





function Player(elementId,videoId, duration){
  this.videoPath  = 'video/'+videoId;
  this.highPath   = this.videoPath+'/high/';
  this.mediumPath = this.videoPath+'/medium/';
  this.poorPath   = this.videoPath+'/poor/';
  this.playerItem = document.getElementById(elementId);
  this.globalId   = elementId;
  this.counter = 0;
  this.partCounter = 0;
  this.playable = true;
  this.inner = '';
  this.parts = duration;
  this.quality = 0;
}
Player.prototype.createVideo = function(itemId){
  item = document.createElement('video');
  item.setAttribute('id', itemId);
  inner='<source src="'+(this.getPath()+this.counter)+'.mp4" type="video/mp4">'
  item.innerHTML = inner;
  item.style.display = 'none';

  startTime = (new Date()).getTime();
  item.load();
  endTime = (new Date()).getTime();
  this.setPath(endTime-startTime);

  player.playerItem.appendChild(item);
}

Player.prototype.hideVideo = function(itemId){
  item = document.getElementById(itemId);
  item.style.display='none';
}

Player.prototype.showVideo = function(itemId){
  item = document.getElementById(itemId);
  item.play();
  item.style.display='block';
}
Player.prototype.update = function() {

  if((this.counter<this.parts)&&(this.partCounter%10==0)&&this.playable){
    this.partCounter=0;
    if(this.counter == 0) {

      newVideoId = this.globalId+this.counter;

      this.createVideo(newVideoId);
      this.showVideo(newVideoId);
      
      this.counter++;
      this.newVideoId = this.globalId+this.counter;

      this.createVideo(this.newVideoId);


    } else {
      this.oldVideoId = this.globalId+(this.counter-1);
      this.hideVideo(this.oldVideoId);

      this.currentVideoId = this.globalId+this.counter;
      this.showVideo(this.currentVideoId);

      this.counter++;
      this.newVideoId   = this.globalId+this.counter;

      this.createVideo(player.newVideoId);
    }
  }
  if(this.playable){
    this.partCounter++;
  }
};
Player.prototype.pauseVideo = function(){
  itemId = player.globalId+(player.counter-1);
  item = document.getElementById(itemId);
  item.pause();
  player.playable = false;
}
Player.prototype.playVideo = function(){
  itemId = player.globalId+(player.counter-1);
  item = document.getElementById(itemId);
  item.play();
  player.playable = true;
}

Player.prototype.startVideo = function(){
  // временный хак
  this.update();
  var fuck = this;
  setInterval(function(){fuck.update.call(fuck)}, 1000);

}

Player.prototype.setPath = function(time){

 if(time<1){
    switch(this.quality){
      case 0: 
        this.quality=1;
        break;
      case 1:
        this.quality=2;
        break;
    }
  } else {
    switch(this.quality){
      case 2: 
        this.quality=1;
        break;
      case 1:
        this.quality=0;
        break;
    }
  }
}
Player.prototype.getPath = function(){
  switch(this.quality){
    case 0:
      return this.poorPath;
    case 1:
      return this.mediumPath;
    case 2:
      return this.highPath;
  }
}
