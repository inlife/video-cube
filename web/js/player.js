

// Player(id, path, parts);

// Parameters:
//     - id {String} id of div for video player
//     - path {String} path with video files
//     - parts {Number} count of 10sec parts

// Examples:
//     var player = new Player('video', '/users/1/video/2/', 40, watch_function);
//     player.startVideo();

// elementId - id дива где будет видео
// video_path - папка видео
// duration - количество кусков
// watch - функция, которая вызывается когда просмотрено больше половины


function Player(elementId , video_path, duration, watch){
  this.videoPath  = video_path;
  this.highPath   = this.videoPath+'720/';
  this.mediumPath = this.videoPath+'360/'; // папки с разными качествами
  this.poorPath   = this.videoPath+'240/';
  this.globalId   = elementId;
  this.wrapperId  = 'video_player_wrapper';
  this.counter = 0; // текущий кусок видео
  this.partCounter = 10; // сколько секунд текущего куска просмотрено
  this.playable = true; // не пауза
  this.parts = parseInt(duration); // общее количество кусков
  this.quality = 1; // среднее качество
  this.lock = true; // false когда происходит загрузка нового куска
  this.newTime = false; // произошла ли перемотка
  this.fullscreen = false; // на полный ли мы экран
  this.watch = watch; // функция набивания просмотров
  this.watched = false;  // вызывали ли мы функцию набивания просмотров
  this.createDom(); // вызываем функцию наполнения дива
  this.volume = 0.7; // громкость 70%

  $(this).on("loaded", { player: this }, function(event){
    event.data.player.createVideo(event.data.player.newVideoId);  // вызывается когда нужно создать новый див с видео
  })
}
Player.prototype.createVideo = function(itemId){
  if(document.getElementById(itemId)){ // если уже такой открывок есть
    return false;
  }
  videoItem = $("<video id='"+itemId+"' src='"+(this.getPath()+this.counter)+".mp4?"+Math.random()+"'></video>"); // создали <video>
  // рандом от кеширования

  this.loadStarted();
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
  item.volume = this.volume;
  item.style.display = 'block';
  item.style.width   = '100%';
  item.style.height  = '100%';
  this.partCounter = 0;
}
Player.prototype.update = function() { // вызывается каждую секунду
  // вывод отладочной информации
  console.log({lock: this.lock, part: this.counter, playable: this.playable, counter: this.partCounter, quality: this.quality, fullscreen: this.fullscreen});

  if(this.counter > (this.parts/2)){ // если просмотрено, то вызываем функцию набивания просмотров
    if(!this.watched){
      this.watch();
      this.watched = true;
    }
  }

  if((this.counter<this.parts)&&(this.partCounter>=10)&&this.playable&&this.lock){

    if(this.counter == 0 || this.newTime) { // только начали смотреть или только что перемотали
      this.newTime = false;

      newVideoId = this.globalId+this.counter; // id video

      this.createVideo(newVideoId); // создаем <video>
      this.showVideo(newVideoId); // и сразу играем

      this.currentVideoId = newVideoId; // для работы громкости

      this.counter++;
      this.newVideoId = this.globalId+this.counter;

      this.partCounter++;

    } else {

      this.oldVideoId = this.globalId+(this.counter-1);
      this.hideVideo(this.oldVideoId); // прячем кусок который только что воспроизводился

      this.currentVideoId = this.globalId+this.counter;
      this.showVideo(this.currentVideoId); // показываем новый кусок

      this.counter++;
      this.newVideoId = this.globalId+this.counter; // выставляем айди для куска который будет загружаться

      setTimeout(function(){ $(this).trigger("loaded") }.bind(this), 1000); // генерируем событие для загрузки спустя 1 сек
    }
  }


  if(this.playable){
    this.partCounter++;
  }

  $('.player-controls.rewind').val(this.counter-1);
}

Player.prototype.pauseVideo = function(){
  item = document.getElementById(this.currentVideoId);
  item.pause();
  this.playable = false;
}
Player.prototype.playVideo = function(){
  this.playable = true;
  if(!this.newTime){
    item = document.getElementById(this.currentVideoId);
    item.play();
  }
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
  this.partCounter = 10;
  this.hideVideo(this.globalId + (this.counter - 1));
  this.newTime = true;
  this.counter = parseInt(value);
}

Player.prototype.createDom = function(){
  $('#' + this.globalId).append('<div id="'+this.wrapperId+'"></div>')
  $('#' + this.wrapperId).append('<div id="player_videos"></div><div class="controls"><div class="play-controls"><button class="player-controls play"></button><button class="player-controls pause"></button><button class="player-controls fullscreen"></button><input class="player-controls volume" type="range" min="0" max="100" value="70"></div><div class="rewind-controls"><input class="player-controls rewind" type="range" min="0" max="' + this.parts + '" value="0"></div></div>');

  this.playerItem = document.getElementById('player_videos'); // переменная в которой хранится див в котором циклически меняются видео
  this.setEvents() // выставляем реакцию на события
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
    // event.data.player is Player
    // $(this) is $('.player-controls.rewind')
  })

  $('.player-controls.volume').on('change', { player: this }, function(event){
    event.data.player.setVolume($(this).val());
  })

  $('.player-controls.fullscreen').on('click', { player: this }, function(event){
    event.data.player.toggleFullScreen();
  })

  $('#player_videos').on('click', { player: this }, function(event){
    if(event.data.player.playable){ // если играет
      event.data.player.pauseVideo(); // останавливаем
    } else {
      event.data.player.playVideo(); // иначе играем
    }
  })
}

Player.prototype.setVolume = function(val){
  this.volume = parseInt(val)/100.0;
  document.getElementById(this.currentVideoId).volume = this.volume;
}

Player.prototype.loadStarted = function(){
  this.loadingTime = Date.now();
  this.lock = false;
  console.log('load started');
}

Player.prototype.loadEnded = function(){
  console.log('load ended');
  this.lock = true;
  this.loadingTime = Date.now() - this.loadingTime;
  this.setPath(this.loadingTime);
  $(this).trigger("loaded");
}

Player.prototype.toggleFullScreen = function(){
  var wrapper = $('#' + this.wrapperId);
  if(this.fullscreen){
    this.fullscreen = false;
    wrapper.attr("style", "height: 100%;");
  } else {
    this.fullscreen = true;
    wrapper = $('#' + this.wrapperId);
    style = "position: fixed; background: #333; right: 0; bottom: 0; min-width: 100%; min-height: 100%; height: 300px; width: auto; z-index: 100;"
    wrapper.attr("style", style);
  }
}
