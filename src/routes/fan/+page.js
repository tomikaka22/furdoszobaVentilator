export async function load({ fetch }) {
	return {
		duration: Number(await ((await fetch('https://furdo.szoba/duration')).text())),
		temporaryTimer: Number(await ((await fetch('https://furdo.szoba/temporaryTimer')).text()))
	};
}