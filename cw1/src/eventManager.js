class EventManager{
    constructor() {
        this.bind = [] // сопоставление клавиш действиям
        this.action = [] // действия
        this.onKeyDown = this.onKeyDown.bind(this);
        this.onKeyUp = this.onKeyUp.bind(this);
    }


    clear(){
        this.bind = [] // сопоставление клавиш действиям
        this.action = [] // действия
    }


    setup(){ // настройка сопоставления
        this.bind[87] = 'up' // w - двигаться вверх
        this.bind[65] = 'left' // a - двигаться влево
        this.bind[83] = 'down' // s - двигаться вниз
        this.bind[68] = 'right' // d - двигаться вправо
        this.bind[32] = 'attack'; // space - атаковать
        document.body.addEventListener("keydown", this.onKeyDown)
        document.body.addEventListener("keyup", this.onKeyUp)
    }
    onKeyDown(event){
        let action = this.bind[event.keyCode]
        if (action){
            this.action[action] = true
        }
    }

    onKeyUp(event){

        let action = this.bind[event.keyCode]
        if(action){
            this.action[action] = false
        }
    }
}

export const eventManager = new EventManager()
