import {Enemy, Player, BonusUpSpeed, BonusUpDmg} from "./entitesManager.js";
import {gameManager} from "./gameManager.js";



class MapManager {
    constructor() {
        this.mapData = null // переменная для хранения карты объекта json
        this.tLayer = null // перемменная для хранения ссылки на блоки карты
        this.xCount = 0 // количество блоков по горизонтали
        this.yCount = 0 // количество блоков по вертикали
        this.tSize = {x: 32, y: 32} // размер блока
        this.mapSize = {x: 32, y: 32} // размер карты в пикселях
        this.tilesets = [] // массив описаний блоков карты (их номера, размеры, координаты)
        this.imgLoadCount = 0
        this.imgLoaded = false
        this.jsonLoaded = false
    }

    clear(){
        this.mapData = null // переменная для хранения карты объекта json
        this.tLayer = null // перемменная для хранения ссылки на блоки карты
        this.xCount = 0 // количество блоков по горизонтали
        this.yCount = 0 // количество блоков по вертикали
        this.tSize = {x: 32, y: 32} // размер блока
        this.mapSize = {x: 32, y: 32} // размер карты в пикселях
        this.tilesets = [] // массив описаний блоков карты (их номера, размеры, координаты)
        this.imgLoadCount = 0
        this.imgLoaded = false
        this.jsonLoaded = false
    }

    parseMap(tilesJSON) {
        this.mapData = JSON.parse(tilesJSON) // разобрать JSON
        this.xCount = this.mapData.width // сохранение ширины
        this.yCount = this.mapData.height // сохранение высоты
        this.tSize.x = this.mapData.tilewidth // сохранение размера блока
        this.tSize.y = this.mapData.tileheight
        this.mapSize.x = this.xCount*this.tSize.x // вычисление размера карты
        this.mapSize.y = this.yCount*this.tSize.y
        for (let i = 0; i < this.mapData.tilesets.length; i++){
            let img = new Image() // переменная для хранения изображения
            img.onload = () => {
                this.imgLoadCount++;
                if (this.imgLoadCount === this.mapData.tilesets.length) {
                    this.imgLoaded = true;
                }
            };
            img.src = this.mapData.tilesets[i].image // задание пути к изображению
            let t = this.mapData.tilesets[i] // забираеем tileset из карты
            let ts = { // создаем свой объект tileset
                firstgid: t.firstgid, // firstgid - с него начинается нумерация в дата
                image: img, // объект рисунка
                name: t.name, // имя элемента рисунка
                xCount: Math.floor(t.imagewidth/this.tSize.x), // горизонтал
                yCount: Math.floor(t.imageheight/this.tSize.y) // вертикаль
            }
            this.tilesets.push(ts) // сохраняем tileset в массив
        }
        this.jsonLoaded = true // true, когда разобрали весь json
    }

    getTileset(tileIndex) {
        for (let i = this.tilesets.length - 1; i >= 0; i--) {
            if (this.tilesets[i].firstgid <= tileIndex) {
                return this.tilesets[i];
            }
        }
        return null;
    }
    getTile(tileIndex){ // индекс блока
        let tile = { // один блок
            img: null, // изображение tileset
            px: 0, py: 0 // координаты блока в tileset
        }
        let tileset = this.getTileset(tileIndex)
        tile.img = tileset.image // изображение искомого tileset
        let id = tileIndex - tileset.firstgid // номер блока в общем массиве data - номер первого блока в отображаемом изображении
        let x = id % tileset.xCount
        let y = Math.floor(id/tileset.xCount)
        tile.px = x * this.tSize.x
        tile.py = y * this.tSize.y
        return tile
    }
    draw(ctx) { // нарисовать карту в контексте
        // если карта не загружена, то повторить прорисовку через 100 мсек
        if (!this.imgLoaded || !this.jsonLoaded){
            setTimeout(() => this.draw(ctx), 100);
        } else {
            if(this.tLayer === null){ // проверить, что tLayer настроен
                for (let id =0; id < this.mapData.layers.length;id++){
                    // проходим по всем layer карты
                    let layer = this.mapData.layers[id]
                    if (layer.type === "tilelayer"){ // если не tilelayer - пропускаем
                        this.tLayer = layer
                        break
                    }
                }
            }
            for(let i = 0; i < this.tLayer.data.length; i++){ // пройти по всей карте
                if (this.tLayer.data[i] !== 0){ // если нет данных - пропускаем
                    let tile = this.getTile(this.tLayer.data[i]) // получение блока по индексу
                    // i проходит линейно по массиву, xCount - длина по x
                    let pX = (i %this.xCount * this.tSize.x) // x в пикселях
                    let pY = Math.floor(i/this.xCount)*this.tSize.y

                   ctx.drawImage(tile.img, tile.px, tile.py, this.tSize.x, this.tSize.y, pX, pY, this.tSize.x, this.tSize.y)
                }
            }
        }
    }
    // принимает путь файла, который необходимо загрузить (если отонсительный, то tiledmap.json)
    loadMap(path) {
        let request = new XMLHttpRequest() // создание ajax-запроса
        request.onreadystatechange = () => {
            if (request.readyState === 4 && request.status === 200) {
                this.parseMap(request.responseText);
            }
        }
        request.open("GET", path, true) // отправить асинхроннай запрос на path с использованием GET
        request.send()
    }

    parseEntities() {
        if (!this.imgLoaded || !this.jsonLoaded) {
            setTimeout(() => this.parseEntities(), 100);
        } else {
            for (let j = 0; j < this.mapData.layers.length; j++) {
                if (this.mapData.layers[j].type === 'objectgroup') {
                    let entitiesLayer = this.mapData.layers[j];
                    for (let i = 0; i < entitiesLayer.objects.length; i++) {
                        let entityData = entitiesLayer.objects[i];
                        try {
                            let entity = this.createEntity(entityData);
                            //console.log(entity)
                            if (entity) {
                                gameManager.entities.push(entity);
                                if (entity.type === "Player") {
                                    gameManager.initPlayer(entity);
                                }
                                if (entity.type === "Enemy") {
                                    gameManager.initEnemy(entity);

                                }
                            }
                        } catch (ex) {
                            console.log("Error while creating entity: ", ex);
                        }
                    }
                }
            }
        }
    }

    createEntity(entityData) {
        switch (entityData.type) {
            case 'Player':
                let player = new Player();
                player.setName(entityData.name);
                player.setPos_x(entityData.x);
                player.setPos_y(entityData.y - 32); // предполагаемая корректировка позиции
                player.setSize_x(entityData.width);
                player.setSize_y(entityData.height);
                player.type = 'Player'
                return player;
            case 'Enemy':
                let enemy = new Enemy();
                enemy.setName(entityData.name);
                enemy.setPos_x(entityData.x);
                enemy.setPos_y(entityData.y - 32);
                enemy.setSize_x(entityData.width);
                enemy.setSize_y(entityData.height);
                enemy.type = 'Enemy'
                return enemy;
            case 'BonusUp':
                let bonusUpSpeed = new BonusUpSpeed();
                bonusUpSpeed.setName(entityData.name);
                bonusUpSpeed.setPos_x(entityData.x);
                bonusUpSpeed.setPos_y(entityData.y - 32);
                bonusUpSpeed.setSize_x(entityData.width);
                bonusUpSpeed.setSize_y(entityData.height);
                bonusUpSpeed.type = 'BonusUp'
                return bonusUpSpeed;

            case 'bonusUpDmg':
                let bonusUpDmg = new BonusUpDmg();
                bonusUpDmg.setName(entityData.name);
                bonusUpDmg.setPos_x(entityData.x);
                bonusUpDmg.setPos_y(entityData.y - 32);
                bonusUpDmg.setSize_x(entityData.width);
                bonusUpDmg.setSize_y(entityData.height);
                bonusUpDmg.type = 'bonusUpDmg'
                return bonusUpDmg;
            default:
                return null;
        }
    }

    getTilesetIdx(x, y){ // использую размеры блоков и количество блоков по горизонтали, вычисляет индекс блока в массиве data
        let idx = Math.floor(y/this.tSize.y)*this.xCount + Math.floor(x/this.tSize.x)
        return this.tLayer.data[idx]

    }

    restartGame(){
        this.mapData = null;
        this.tLayer = null;
        this.xCount = 0;
        this.yCount = 0;
        this.tilesets = [];
        this.imgLoadCount = 0;
        this.imgLoaded = false;
        this.jsonLoaded = false;
    }
}


export const mapManager = new MapManager()