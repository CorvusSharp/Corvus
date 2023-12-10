class SoundManager {
    constructor() {
        this.clips = {} // для хранения всех аудиофайлов по именам
        this.context = null // аудиоконтекст
        this.gainNode = null // главный узел для управления громкостью звука
        this.loaded = false // все звуки загружены
    }
    init(){ // инициализация менеджера звука
        this.context = new AudioContext() // создание контекста звука
        this.gainNode = this.context.createGain ? this.context.createGain() : this.context.createGainNode()
        this.gainNode.connect(this.context.destination) // подключение к динамикам
    }
    load(path, callback){ // загрузка одного аудиофайла
        if(this.clips[path]){ // проверяем, что уже загружены
            callback(this.clips[path]) // вызываем загруженный
            return // выход
        }
        let clip = {path: path, buffer: null, loaded: false}
        clip.play = (volume, loop) => this.play(this.clips[path].path, {looping: loop ? loop : false, volume: volume ? volume: 1})
        this.clips[path] = clip // помещаем в "массив" (литерал)
        let request = new XMLHttpRequest()
        // создание асинхронного запроса
        request.open('GET', path, true)
        request.responseType = 'arraybuffer'
        // тип результата - байты
        request.onload = () => {
            this.context.decodeAudioData(
                request.response,
                function(buffer) {
                    clip.buffer = buffer;
                    clip.loaded = true;
                    callback(clip);
                }
            );
        };
        request.send()
    }
    loadArray(array) {
        for (let i = 0; i < array.length; i++) {
            this.load(array[i], () => { // использование стрелочной функции здесь
                if (array.length === Object.keys(this.clips).length) {
                    for (let sd in this.clips) {
                        if (!this.clips[sd].loaded) {
                            return;
                        }
                    }
                    this.loaded = true;
                }
            });
        }
    }
    play(path, settings){ // проигрывание файла
        if(!this.loaded){ // если все еще не загрузили
            setTimeout(() => this.play(path, settings), 1000)
            return
        }
        let looping = false
        let volume = 1
        if (settings){ // если переопределены, то перенастраиваем значения
            if(settings.looping){
                looping = settings.looping
            }
            if(settings.volume){
                volume = settings.volume
            }
        }
        let sd = this.clips[path] // получаем звуковой эффект
        if (sd === null){
            return false
        }
        let sound = this.context.createBufferSource()
        sound.buffer = sd.buffer
        sound.connect(this.gainNode)
        sound.loop = looping
        this.gainNode.gain.value = volume
        sound.start(0)
        return true
    }
}

export const soundManager = new SoundManager()