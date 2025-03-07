(function() {
  // Rimuove le righe con data-testid="recommended-track"
  const recommendedTracks = document.querySelectorAll('[data-testid="recommended-track"]');
  recommendedTracks.forEach(track => track.remove());

  const esplicito = document.querySelectorAll('[aria-label="Esplicito"]');
  esplicito.forEach(track => track.remove());

  // Estrae e stampa il contenuto delle righe rimanenti
  const rows = document.querySelectorAll('[data-testid="tracklist-row"]');
  let output = [];

  rows.forEach(row => {
    const col2Div = row.querySelector('[aria-colindex="2"]');
    const col3Anchor = row.querySelector('[aria-colindex="3"] a');

    const col2Content = col2Div ? col2Div.textContent.trim() : '';
    const col3Content = col3Anchor ? col3Anchor.textContent.trim() : '';

    output.push(`${col2Content} ${col3Content}`);
  });

  console.log(output.join('\n'));
})();