//$RCSfile: KStopwatch.js,v $: script file
//$Revision: 1.1 $ $Date: 2014/09/04 22:11:54 $
//$Author: ddarko $
//
//Stopwatch
//2012-12  https://gist.github.com/electricg/4372563


//------------------------------------------------------------------------------
/*Stopwatch
	Example:
			<html>
			<head>
				<title>Stopwatch</title>
			</head>
			<body onload="show();">
				<div>Time: <span id="time"></span></div>
				<input type="button" value="start" onclick="start();">
				<input type="button" value="stop" onclick="stop();">
				<input type="button" value="reset" onclick="reset()">
			</body>
			</html>
	
 */
function CStopwatch() {
	var	startAt	= 0; // time of last start / resume. (0 if not running)
	var	lapTime	= 0; // time  [ms] when stopwatch last stopped in milliseconds

	//-------------------------------------------------------------------------
	/*Returns current time
	 */
	var	now	= function() {
		return (new Date()).getTime();
	};

	//-------------------------------------------------------------------------
	/* Start or resume stopwatch
	 */
	this.start = function() {
		startAt = startAt ? startAt : now();
	};

	//-------------------------------------------------------------------------
	/* Stop or pause stopwatch
	 */
	 this.stop = function() {
		lapTime	= startAt ? lapTime + now() - startAt : lapTime;
		startAt	= 0;
		clearInterval(this.timer);

	};

	this.reset = function() {
		lapTime = startAt = 0;
	};

	this.time = function() {
		return lapTime + (startAt ? now() - startAt : 0);
	};

	//-------------------------------------------------------------------------
	/*Format padding
	 */
	var pad = function(num, size) {
		var s = "0000" + num;
		return s.substr(s.length - size);
	}

	//-------------------------------------------------------------------------
	/*Returns lapsed time in the format hh:mm:ss.ms (hh > 0)
	 */
	this.toString = function(){
	var h = m = s = ms = 0;
	var strResult = '';
 
	h = Math.floor( time / (60 * 60 * 1000) );
	time = time % (60 * 60 * 1000);
	m = Math.floor( time / (60 * 1000) );
	time = time % (60 * 1000);
	s = Math.floor( time / 1000 );
	ms = time % 1000;
 
	if (h > 0 )
		strResult = pad(h, 2)  + ':' ;
	strResult =  pad(m, 2) + ':' + pad(s, 2) + '.' + pad(ms, 3);

	return strResult;
	};

};
///////////////////////////////////////////////////////////////////////////////
