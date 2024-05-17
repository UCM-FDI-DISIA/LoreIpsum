const c = document.querySelector('canvas')
const ctx = c.getContext('2d')
let cw = c.width = innerWidth
let ch = c.height = innerHeight
const dots = Array(500)
const dur = 22
const dist = 120
const hue = 13
const img = new Image()
const img2 = new Image()
const imgProps = {w:2000, h:1850, src:'https://images.unsplash.com/photo-1704121355552-10ac4d5b1677?q=80&w=2000', src2:'data:image/jpg;base64,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'}

for (let i=0; i<dots.length; i++) dots[i] = {}

img.src = imgProps.src
img2.src = imgProps.src2
setImgProps()

const tl = gsap.timeline({ onUpdate:redraw })
.fromTo(imgProps, {
  a:1
},{
  duration:dur/4,
  yoyo:true,
  ease:'sine.inOut',
  a:0.7,
  repeat:-1
}, 0)
.fromTo(dots, {
  a:0
},{
  duration:dur/2,
  yoyoEase:'expo.in',
  ease:'expo',
  a:1,
  stagger:{amount:dur, repeat:-1}
}, 0)
.fromTo(dots, {
  x:()=> cw*Math.random(),
  y:()=> ch*Math.random(),
  r: 1,
  h: hue,
  s:()=>'random(45,60,1)',
  l:()=>'random(35,60,1)'
},{
  duration:dur,
  ease:'sine.inOut',
  motionPath:()=>'M'+cw*Math.random()+','+ch*Math.random()+'c'+gsap.utils.random(-dist,dist)+','+gsap.utils.random(-dist,dist)+' '+gsap.utils.random(-dist,dist)+','+gsap.utils.random(-dist,dist)+' 0,0',
  r:()=>'+=random(-1,1.2)',
  repeatRefresh:true,
  stagger:{amount:dur, repeat:-1},
}, 0)
.seek(dur) //fast-forward past the initial run


function drawDot(dot){
  ctx.fillStyle = 'hsla('+dot.h+','+dot.s+'%,'+dot.l+'%,'+dot.a+')'
  ctx.beginPath()
  ctx.arc(dot.x, dot.y, dot.r, 0, 2*Math.PI)
  ctx.fill()
}

function redraw(){
  ctx.clearRect(0,0,cw,ch)
  ctx.drawImage(img, cw/2-imgProps.w/2, scrollY/2, imgProps.w, imgProps.h)
  ctx.globalCompositeOperation = 'lighter'
  dots.forEach(dot => drawDot(dot))
  ctx.globalAlpha = imgProps.a
  ctx.globalCompositeOperation = 'multiply'
  ctx.drawImage(img2, cw/2-imgProps.w/2, scrollY/2, imgProps.w, imgProps.h)
  ctx.globalCompositeOperation = 'screen'
  ctx.globalAlpha = 1
  ctx.drawImage(img, cw/2-imgProps.w/2, scrollY/2, imgProps.w, imgProps.h)
}

function setImgProps(){
  if (cw>ch*1.08) { imgProps.w=cw; imgProps.h=cw*0.925 }
  else { imgProps.w=ch*1.08; imgProps.h=ch }
}

window.onresize = ()=>{
  cw = c.width = innerWidth
  ch = c.height = innerHeight
  setImgProps()
  tl.invalidate()
}

window.onclick = ()=> tl.isActive()? tl.pause() : tl.play() //toggle play on click