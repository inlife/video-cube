

// Player(id, path, parts);

// Parameters:
//     - id {String} id of div for video player
//     - path {String} path with video files
//     - parts {Number} count of 10sec parts

// Examples:
//     var player = new Player('video', '/users/1/video/2/', 40, watch_function);
//     player.startVideo();


function Player(elementId , video_path, duration, watch){
  this.videoPath  = video_path;
  this.highPath   = this.videoPath+'720/';
  this.mediumPath = this.videoPath+'360/';
  this.poorPath   = this.videoPath+'240/';
  this.globalId   = elementId;
  this.wrapperId  = 'video_player_wrapper';
  this.counter = 0;
  this.partCounter = 0;
  this.playable = true;
  this.inner = '';
  this.parts = parseInt(duration);
  this.quality = 1;
  this.lock = true;
  this.newTime = false;
  this.fullscreen = false;
  this.watch = watch;
  this.watched = false;

  this.createDom();
}
Player.prototype.createVideo = function(itemId){
  this.loadStarted();
  if(document.getElementById(itemId)){ // если уже такой открывок есть
    return false;
  }
  videoItem = $("<video id='"+itemId+"' src='"+(this.getPath()+this.counter)+".mp4'></video>");

  videoItem.on('loadedmetadata', { player: this }, function(event){
    event.data.player.loadEnded();
  });

  videoItem.hide();

  $(this.playerItem).append(videoItem);
}

Player.prototype.hideVideo = function(itemId){
  $('#'+itemId).remove();
}

Player.prototype.showVideo = function(itemId){
  item = document.getElementById(itemId);
  item.play();
  item.style.display = 'block';
  item.style.width   = '100%';
  item.style.height  = '100%';
}
Player.prototype.update = function() {
  console.log({lock: this.lock, part: this.counter, playable: this.playable, counter: this.partCounter, quality: this.quality, fullscreen: this.fullscreen});

  if(this.counter > (this.parts/2)){
    if(!this.watched){
      this.watch();
      this.watched = true;
    }
  }
  if(!this.lock) {
    this.partCounter--;
  }
  if((this.counter<this.parts)&&(this.partCounter%10==0)&&this.playable){
    this.partCounter = 0;

    if(this.counter == 0 || this.newTime) {
      this.newTime = false;

      newVideoId = this.globalId+this.counter;

      this.createVideo(newVideoId);
      this.showVideo(newVideoId);

      this.counter++;
      this.newVideoId = this.globalId+this.counter;

      setTimeout(function(){ this.createVideo(this.newVideoId) }.bind(this), 1000);

      this.partCounter++;

    } else if(this.lock) {

      this.oldVideoId = this.globalId+(this.counter-1);
      this.hideVideo(this.oldVideoId);

      this.currentVideoId = this.globalId+this.counter;
      this.showVideo(this.currentVideoId);

      this.counter++;
      this.newVideoId = this.globalId+this.counter;

      setTimeout(function(){ this.createVideo(this.newVideoId) }.bind(this), 1000);
    }
  }

  this.partCounter++;
  $('.player-controls.rewind').val(this.counter-1);
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

 if(time<4000){
    if(this.quality<2) this.quality++;
  }
  if(time>6000){
    if(this.quality>0) this.quality--;
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

Player.prototype.goTo = function(value){
  this.partCounter = 0;
  this.hideVideo(this.globalId + (this.counter - 1));
  this.newTime = true;
  this.counter = parseInt(value);
}

Player.prototype.createDom = function(){
  $('#' + this.globalId).append('<div id="'+this.wrapperId+'"></div>')
  $('#' + this.wrapperId).append('<div id="player_videos"></div>')
  $('#' + this.wrapperId).append('<div class="play-controls"></div>')
  $('#' + this.wrapperId).append('<div class="rewind-controls"></div>')
  $('#' + this.wrapperId + ' .play-controls').append('<button class="player-controls play">▶</button>')
  $('#' + this.wrapperId + ' .play-controls').append('<button class="player-controls pause">||</button>')
  $('#' + this.wrapperId + ' .play-controls').append('<button class="player-controls fullscreen">⬚</button>')
  $('#' + this.wrapperId + ' .rewind-controls').append('<input class="player-controls rewind" type="range" min="0" max="'+this.parts+'" value="0" />')

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

  $('.player-controls.fullscreen').on('click', { player: this }, function(event){
    event.data.player.toggleFullScreen();
  })
}

Player.prototype.loadStarted = function(){
  this.lock = false;
  this.loadingTime = Date.now();
}

Player.prototype.loadEnded = function(){
  this.lock = true;
  this.loadingTime = Date.now() - this.loadingTime;
  this.setPath(this.loadingTime);
}

Player.prototype.toggleFullScreen = function(){
  if(this.fullscreen){
    this.fullscreen = false;
    wrapper.attr("style", "");
  } else {
    this.fullscreen = true;
    wrapper = $('#' + this.wrapperId);
    style = "position: fixed; right: 0; bottom: 0; min-width: 100%; min-height: 100%; width: auto; height: auto; z-index: 100;"
    wrapper.attr("style", style);
  }
}