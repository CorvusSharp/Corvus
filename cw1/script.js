document.addEventListener('DOMContentLoaded', function() {
    const playerNameInput = document.getElementById('player-name');
    const startGameButton = document.getElementById('start-game');

    // Загрузка последнего введенного имени из localStorage
    const lastPlayerName = localStorage.getItem('lastPlayerName');
    if (lastPlayerName) {
        playerNameInput.value = lastPlayerName;
    }

    startGameButton.addEventListener('click', function() {
        const playerName = playerNameInput.value.trim();

        if (!playerName) {
            alert('Пожалуйста, введите имя персонажа.');
            return;
        }

        // Сохранение имени игрока в localStorage
        localStorage.setItem('lastPlayerName', playerName);

        // Перенаправление на main.html
        window.location.href = 'main.html';
    });
});
