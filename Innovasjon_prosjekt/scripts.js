var rom1 = document.querySelector("#rom1");
var rom2 = document.querySelector("#rom2");
var rom3 = document.querySelector("#rom3");
var rom4 = document.querySelector("#rom4");

var fase1 = document.querySelector("#fase1");
var fase2 = document.querySelector("#fase2");
var fase3 = document.querySelector("#fase3");
var fase4 = document.querySelector("#fase4");

var teller3 = rom3.innerText.split(':');

function nedtelling(){
    var teller1 = rom1.innerText.split(':');
    var teller2 = rom2.innerText.split(':');
    var teller3 = rom3.innerText.split(':');
    var teller4 = rom4.innerText.split(':');

    if (teller1.length == 3){

        nedtelt1 = nedtellerhjelper(teller1)
        rom1.innerText=nedtelt1
        skiftefase(teller1, fase1)

    }
    if (teller2.length == 3){
        nedtelt2 = nedtellerhjelper(teller2)
        rom2.innerText=nedtelt2
        skiftefase(teller2, fase2)
    }
    if (teller3.length == 3){
        nedtelt3 = nedtellerhjelper(teller3)
        rom3.innerText=nedtelt3
        skiftefase(teller3, fase3)
    }
    if (teller4.length == 3){
        nedtelt4 = nedtellerhjelper(teller4)
        rom4.innerText=nedtelt4
        skiftefase(teller4, fase4)
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
            if (min == 30){
            }
            time -= 1
            if (time<0){
                return "Ferdig"
            }
        }
    }
    time = time.toString()
    min = min.toString()
    sekunder = sekunder.toString()
    if(min<10){
        nedtelt = "0" + time+":0"+min+":"+sekunder
    }
    else{
        nedtelt = "0" + time+":"+min+":"+sekunder
    }
    return nedtelt
}

function skiftefase(tidsarray, faseElement){
    //console.log(faseElement)
    time = parseInt(tidsarray[0])
    min = parseFloat(tidsarray[1])
    sekunder = parseInt(tidsarray[2])
    if (30>min){
        console.log("hei")
    }
    if(min>31){
        return "Nylig injisert, vent."
    }
    if (31>min && min>14){
        faseElement.innerText="Drikke."
    }
    if(15>min && min>1){
        faseElement.innerText="Gå på do."
    } 
    if(0>sekunder){
        faseElement.innerText="Gå til petskan."
    }
}
// Fasene Injisering 60-30. 30-15 drikke, 15-0 Gå på do, 0 gå på petskan.


x = setInterval(nedtelling, 1000);