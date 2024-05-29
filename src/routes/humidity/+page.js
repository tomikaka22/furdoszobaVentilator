export async function load({ fetch }) {
	return {
		thresh: Number(await ((await fetch('https://furdo.szoba/thresh')).text()))
	};
}