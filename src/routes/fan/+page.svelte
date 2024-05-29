<script>
	import { invalidateAll } from '$app/navigation';

	export let data;
console.log(Math.abs(data.duration));
	let form;
	let state = 1;

	console.log(data);

	function submit() {
		if (form.duration.value > 9999)
			form.duration.value = 9999;

		if (data.duration)
			resetFAN();
		else if (state)
			submitON();
		else
			submitOFF();
	}

	async function resetFAN() {
		const formData = new FormData(form);
		formData.set('duration', 1);

		const response = await fetch(form.action, {
			method: 'POST',
			body: formData
		});

		if (response.ok) {
			invalidateAll();
			form.duration.value = '';
		}
	}

	async function submitOFF() {
		const formData = new FormData(form);
		formData.set('duration', 0 - form.duration.value * 60000);

		const response = await fetch(form.action, {
			method: 'POST',
			body: formData
		});

		if (response.ok) {
			invalidateAll();
			form.duration.value = '';
		}
	}

	async function submitON() {
		const formData = new FormData(form);
		formData.set('duration', form.duration.value * 60000);

		const response = await fetch(form.action, {
			method: 'POST',
			body: formData
		});

		if (response.ok) {
			invalidateAll();
			form.duration.value = '';
		}
	}
</script>
<main class="absolute top-0 bottom-0 left-0 right-0 -z-10 flex justify-center items-center">

	<div class="mb-10">
		<form class:disable={ data.temporaryTimer && data.duration } class="flex justify-center items-center flex-col gap-4" bind:this={form} action="https://furdo.szoba/post" method="POST">
			<p class="font-semibold text-primary text-3xl text-center p-0 leading-5">Perc</p>
			<input class="transition-all text-center text-primary focus:outline-none focus:bg-primary focus:text-on-primary
				focus:placeholder:text-on-primary placeholder:text-center
				placeholder:text-primary placeholder:text-8xl
				outline outline-2 px-2 py-2 caret-[transparent] rounded-full w-64 text-8xl max-w-fit bg-background"
				type="number" name="duration" placeholder="0"
			>
			<div class="flex gap-2">
				<button class:activeButton={ state === 1 } class="outline outline-1 px-4 py-1 rounded-3xl font-semibold transition-all" on:click|preventDefault={() => { state = 1; }}>Bekapcsol</button>
				<button class:activeButton={ state === 0 } class="outline outline-1 px-4 py-1 rounded-3xl font-semibold transition-all" on:click|preventDefault={() => { state = 0; }}>Kikapcsol</button>
			</div>
		</form>
		<div class="flex justify-center mt-4">
			{#if !data.duration}
				<button on:click={submit} class="w-28 outline outline-1 px-4 py-1 rounded-3xl font-semibold transition-all focus:outline-none focus:bg-primary focus:text-on-primary focus:rounded-lg">Start</button>
			{:else}
				<button on:click={submit} class="w-28 outline outline-1 outline-error text-error px-4 py-1 rounded-3xl font-semibold transition-all focus:outline-none focus:bg-primary focus:text-on-primary focus:rounded-lg">Stop</button>
			{/if}
		</div>
		<div class:opacity-100={ data.temporaryTimer && data.duration } class="flex justify-center items-center mt-8 gap-2 opacity-0 transition-all">
			<progress class="transition-all duration-500 rounded-[6px] bg-foreground" max="{Math.abs(data.duration)}" value="{data.temporaryTimer}"></progress>
			<p>{ data.temporaryTimer / 60000 > 1 ? (data.temporaryTimer / 60000).toFixed(0) : '< 1' } Perc</p>
		</div>
	</div>

</main>

<style lang="postcss">
	/* Chrome, Safari, Edge, Opera */
	input::-webkit-outer-spin-button,
	input::-webkit-inner-spin-button {
		-webkit-appearance: none;
		margin: 0;
	}

	/* Firefox */
	input[type=number] {
		-moz-appearance: textfield;
	}

	.activeButton {
		@apply outline-none rounded-lg bg-primary text-on-primary;
	}

	::-webkit-progress-value {
		transition: all 1s ease;
	}

	::-moz-progress-bar {
		@apply bg-primary;
		transition: all 1s ease;
	}

	::-webkit-progress-bar {
		@apply bg-foreground rounded-[6px];
	}

	::-webkit-progress-value {
		@apply bg-primary rounded-[6px];
	}

	.disable {
		@apply pointer-events-none opacity-45;
	}
</style>