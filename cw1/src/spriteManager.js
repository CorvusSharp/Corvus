class SpriteManager {
    constructor() {
        this.image = new Image() // рисунок с объектами
        this.sprites = [] // массив объектов для отображения
        this.imgLoaded = false // изображения загружены
        this.jsonLoaded = false //// JSON загружен
    }

    clear(){
        this.image = new Image() // рисунок с объектами
        this.sprites = [] // массив объектов для отображения
        this.imgLoaded = false // изображения загружены
        this.jsonLoaded = false //// JSON загружен
    }


    loadAtlas(atlasJson, atlasImg) {
        let request = new XMLHttpRequest() // создаем запрос
        request.onreadystatechange = () => { // ждем ответа от сервера
            if (request.readyState === 4 && request.status === 200) {
                this.parseAtlas(request.responseText) // разбираем атлас
            }
        }
        request.open("GET", atlasJson, true) // открываем запрос
        request.send() // отправляем запрос
        this.image.onload = () => { // ждем загрузки изображения
            this.imgLoaded = true
        }
        this.image.src = atlasImg // задаем путь к изображению
    }

    parseAtlas(atlasJSON) {
        let atlas = JSON.parse(atlasJSON) // разобрать JSON
        for (let name in atlas.frames) { // проход по всем именам в frames
            let frame = atlas.frames[name].frame // получение спрайта из атласа
            this.sprites.push({ // добавление спрайта в массив
                name: name,
                x: frame.x,
                y: frame.y,
                w: frame.w,
                h: frame.h
            })
        }
        this.jsonLoaded = true // все спрайты загружены
    }

    drawSprite(ctx, name, x, y) {

        if (!this.imgLoaded || !this.jsonLoaded) {
            setTimeout(() => this.drawSprite(ctx, name, x, y), 100)

        } else {
            let sprite = this.getSprite(name) // получить спрайт по имени
            if (!sprite) {
                return
            }
            ctx.drawImage(this.image, sprite.x, sprite.y, sprite.w, sprite.h, x, y, sprite.w, sprite.h)
        }
    }

    getSprite(name) {
        for (let i = 0; i < this.sprites.length; i++) {
            let s = this.sprites[i]
            if (s.name === name) {
                return s
            }
        }
        return null
    }

}

export const spriteManager = new SpriteManager()