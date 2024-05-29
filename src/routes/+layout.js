export const prerender = true;
export const ssr = false;

export async function load({ fetch }) {
	return {
		temp: Number(await ((await fetch('https://furdo.szoba/temp')).text())),
		hum: Number(await ((await fetch('https://furdo.szoba/hum')).text())),
		relay: Boolean(Number(await ((await fetch('https://furdo.szoba/relay')).text())))
	};
}