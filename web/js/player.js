

// Player(id, path, parts);

// Parameters:
//     - id {String} id of div for video player
//     - path {String} path with video files
//     - parts {Number} count of 10sec parts

// Examples:
//     var player = new Player('video', '/users/1/video/2/', 40);
//     player.startVideo();


function Player(elementId , video_path, duration){
  this.videoPath  = video_path;
  this.highPath   = this.videoPath+'/720/';
  this.mediumPath = this.videoPath+'/360/';
  this.poorPath   = this.videoPath+'/240/';
  this.globalId   = elementId;
  this.counter = 0;
  this.partCounter = 0;
  this.playable = true;
  this.inner = '';
  this.parts = duration;
  this.quality = 1;
  this.lock = true;
  this.newTime = false;

  this.createDom();
}
Player.prototype.createVideo = function(itemId){
  item = document.getElementById(itemId);
  if(item){
    return false;
  }
  item = document.createElement('video');
  item.setAttribute('id', itemId);
  inner = '<source src="'+(this.getPath()+this.counter)+'.mp4" type="video/mp4">'
  item.innerHTML = inner;
  item.style.display = 'none';

  startTime = (new Date()).getTime();
  this.lock = false;
  item.load()
  this.lock = true;

  endTime = (new Date()).getTime();
  this.setPath(endTime-startTime);

  this.playerItem.appendChild(item);
}

Player.prototype.hideVideo = function(itemId){
  item = document.getElementById(itemId);
  if(item){
    item.pause();
    item.currentTime = 0;
    item.style.display = 'none';
  }
}

Player.prototype.showVideo = function(itemId){
  item = document.getElementById(itemId);
  item.play();
  item.style.display = 'block';
  item.style.width   = '100%';
  item.style.height  = '100%';
}
Player.prototype.update = function() {

  if((this.counter<this.parts)&&(this.partCounter%10==0)&&this.playable){
    this.partCounter = 0;

    if(this.counter == 0 || this.newTime) {
      this.newTime = false;

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
      this.newVideoId = this.globalId+this.counter;

      this.createVideo(this.newVideoId);
    }
  }

  // console.log($('.player-controls.rewind'));
  $('.player-controls.rewind').val(this.counter);

  if(this.playable&&this.lock){
    this.partCounter++;
  }
}

Player.prototype.pauseVideo = function(){
  itemId = this.globalId+(this.counter-1);
  item = document.getElementById(itemId);
  item.pause();
  this.playable = false;
}
Player.prototype.playVideo = function(){
  itemId = this.globalId+(this.counter-1);
  item = document.getElementById(itemId);
  item.play();
  this.playable = true;
}

Player.prototype.startVideo = function(){
  this.update();
  var self = this; // hack for 'this' forwarding into update
  setInterval(function(){self.update.call(self)}, 1000);

}

Player.prototype.setPath = function(time){

 if(time<5){
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

Player.prototype.goTo = function(value) {
  this.partCounter = 0;
  this.hideVideo(this.globalId + (this.counter - 1));
  this.newTime = true;
  this.counter = value;
}

Player.prototype.createDom = function(){
  $('#' + this.globalId).append('<div id="player_videos"></div>')
  $('#' + this.globalId).append('<div class="play-controls"></div>')
  $('#' + this.globalId).append('<div class="rewind-controls"></div>')
  $('#' + this.globalId + ' .play-controls').append('<button class="player-controls play">Play</button>')
  $('#' + this.globalId + ' .play-controls').append('<button class="player-controls pause">Pause</button>')
  $('#' + this.globalId + ' .rewind-controls').append('<input class="player-controls rewind" type="range" min="0" max="'+this.parts+'" value="0" />')

  this.playerItem = document.getElementById('player_videos');
  this.setEvents()
}

Player.prototype.setEvents = function(){
  $('.player-controls.play').on('click', { player: this }, function(event){
    event.data.player.playVideo();
  })

  $('.player-controls.pause').on('click', { player: this }, function(event){
    event.data.player.pauseVideo();
  })

  $('.player-controls.rewind').on('change', { player: this }, function(event){
    event.data.player.goTo($(this).val());
  })
}