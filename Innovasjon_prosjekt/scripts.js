var rom1 = document.querySelector("#rom1");
var rom2 = document.querySelector("#rom2");
var rom3 = document.querySelector("#rom3");
var rom4 = document.querySelector("#rom4");

var teller3 = rom3.innerText.split(':');

function nedtelling(){
    console.log("hei")
    var teller1 = rom1.innerText.split(':');
    var teller2 = rom2.innerText.split(':');
    var teller3 = rom3.innerText.split(':');
    var teller4 = rom4.innerText.split(':');

    if (teller1.length == 3){
        nedtelt1 = nedtellerhjelper(teller1)
        rom1.innerText=nedtelt1

    }
    if (teller2.length == 3){
        nedtelt2 = nedtellerhjelper(teller2)
        rom2.innerText=nedtelt2

    }
    if (teller3.length == 3){
        nedtelt3 = nedtellerhjelper(teller3)
        rom3.innerText=nedtelt3

    }
    if (teller4.length == 3){
        nedtelt4 = nedtellerhjelper(teller4)
        rom4.innerText=nedtelt4

    }
}
function nedtellerhjelper(array){
    time = parseInt(array[0])
    min = parseFloat(array[1])
    sekunder = parseInt(array[2])
    sekunder -= 1
    if (sekunder <= 0){
        sekunder = 60
        min -= 1
        if (min <= 0){
            min = 60
            time -= 1
            if (time<0){
                return "Ferdig"
            }
        }
    }
    time = time.toString()
    min = min.toString()
    sekunder = sekunder.toString()
    nedtelt = time+":"+min+":"+sekunder
    return nedtelt
}


x = setInterval(nedtelling, 1000);