document.addEventListener("DOMContentLoaded", () => {
  const year = document.getElementById("year");
  if (year) year.textContent = new Date().getFullYear();

  const greetBtn = document.getElementById("greet-btn");
  const demoText = document.getElementById("demo-text");
  if (greetBtn && demoText) {
    greetBtn.addEventListener("click", () => {
      const h = new Date().getHours();
      const msg = h < 12 ? "Good morning!" : h < 18 ? "Good afternoon!" : "Good evening!";
      demoText.textContent = `${msg} Thanks for visiting.`;
    });
  }

  // Contact form confirmation
  const form = document.getElementById("contact-form");
  const alertArea = document.getElementById("alert-area");
  if (form && alertArea) {
    form.addEventListener("submit", (e) => {
      e.preventDefault();
      alertArea.innerHTML = `
        <div class="alert alert-success" role="alert">
          Thank you! Your message has been sent (demo).
        </div>`;
      form.reset();
    });
  }
});
