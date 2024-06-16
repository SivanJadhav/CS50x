document.addEventListener('DOMContentLoaded', (event) => {
    const form = document.getElementById('countryForm');

    form.addEventListener('submit', function(event) {
        event.preventDefault();  // Prevent the form from submitting the traditional way
        const country = document.getElementById('country').value;
        alert(`We Love ${country}!`);
    });
});